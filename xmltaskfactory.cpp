#include "xmltaskfactory.h"
#include "xmltaskfactory_p.h"
#include "task.h"

#include <QDebug>
#include <QtGlobal>

XmlTaskFactory::XmlTaskFactory(QObject *parent) :
    QObject(parent), QAbstractXmlReceiver(), d(new XmlTaskFactoryPrivate)
{
    // Build statemachine:
    QState *root = new QState();
    QState *in_taskseries = new QState();
    QState *taskseries_root = new QState(in_taskseries);
    QState *in_tags = new QState(in_taskseries);
    QState *in_tag = new QState(in_taskseries);
    QState *in_participants = new QState(in_taskseries);
    QState *in_contact = new QState(in_taskseries);
    QState *in_notes = new QState(in_taskseries);
    QState *in_note = new QState(in_taskseries);
    QState *in_task = new QState(in_taskseries);
    d->sm.addState(root);
    d->sm.addState(in_taskseries);
    in_taskseries->setInitialState(taskseries_root);

    // from root we can go in taskseries
    root->addTransition(this, SIGNAL(enterTaskseriesElement()), in_taskseries);
    // taskseries entry controls task instance creation
    connect(in_taskseries, SIGNAL(entered()), SLOT(startCreateTask()));
    connect(in_taskseries, SIGNAL(exited()), SLOT(finishCreateTask()));
    // from taskseries we enter any of a number of child nodes and back again
    taskseries_root->addTransition(this, SIGNAL(enterTagsElement()), in_tags);
    in_tags->addTransition(this, SIGNAL(leaveCurrentElement()), taskseries_root);
    taskseries_root->addTransition(this, SIGNAL(enterNotesElement()), in_notes);
    in_notes->addTransition(this, SIGNAL(leaveCurrentElement()), taskseries_root);
    taskseries_root->addTransition(this, SIGNAL(enterParticipantsElement()), in_participants);
    in_participants->addTransition(this, SIGNAL(leaveCurrentElement()), taskseries_root);
    taskseries_root->addTransition(this, SIGNAL(enterTaskElement()), in_task);
    in_task->addTransition(this, SIGNAL(leaveCurrentElement()), taskseries_root);
    // from tags we go into tag children
    in_tags->addTransition(this, SIGNAL(enterTagElement()), in_tag);
    in_tag->addTransition(this, SIGNAL(leaveCurrentElement()), in_tags);
    // leaving tag adds the last seen text node as a tag to the current task
    connect(in_tag, SIGNAL(exited()), SLOT(addTagToCurrentTask()));
    // from participants into contacts and back
    in_participants->addTransition(this, SIGNAL(enterContactElement()), in_contact);
    in_contact->addTransition(this, SIGNAL(leaveCurrentElement()), in_participants);
    // from notes into note and back
    in_notes->addTransition(this, SIGNAL(enterNoteElement()), in_note);
    in_note->addTransition(this, SIGNAL(leaveCurrentElement()), in_notes);
    // leaving taskseries takes us back to root
    taskseries_root->addTransition(this, SIGNAL(leaveCurrentElement()), root);

    // start at root.
    d->sm.setInitialState(root);
    d->sm.start();
}

XmlTaskFactory::~XmlTaskFactory()

{
    delete d;
}

void XmlTaskFactory::setSource(QIODevice *source)
{
    // Build and evaluate query
    d->query.bindVariable("input", source);
    d->query.setQuery("doc($input)/rsp/tasks/list/taskseries");
    d->query.evaluateTo(this);
}

void XmlTaskFactory::atomicValue(const QVariant &/*value*/)
{
}

void XmlTaskFactory::attribute(const QXmlName &name, const QStringRef &value)
{
    QString attributeName = name.localName(d->query.namePool());
    QString nodeName = d->currentElementName.localName(d->query.namePool());
    qDebug() << "Hit attribute" << attributeName << "in" << nodeName;
    if (nodeName == "taskseries" && attributeName == "name") {
        Q_ASSERT_X(d->currentTask != 0, "XmlTaskFactory::attribute", "No current task");
        d->currentTask->setTitle(value.toString());
        qDebug() << "Set current task title to" << d->currentTask->title();
    } else if (nodeName == "task" && attributeName == "due") {
        Q_ASSERT_X(d->currentTask != 0, "XmlTaskFactory::attribute", "No current task");
        QString stamp = value.toString().trimmed();
        if (!stamp.isEmpty()) {
            // RTM returns all timestamps in UTC but QDateTime
            // can't parse the trailing "Z" from the RFC-3339 notation,
            // so we explicitly set the QDateTime to UTC and chop off the
            // "Z"
            QDateTime due = QDateTime::fromString(stamp.left(stamp.length() - 1), Qt::ISODate);
            if (!due.isValid() || due.isNull()) {
                qWarning() << "Unable to parse due timestamp:" << value.toString();
            } else {
                due.setTimeSpec(Qt::UTC);
                d->currentTask->setDue(due);
                qDebug() << "Set current task due to"
                         << due.toString();
            }
        }
    }
}

void XmlTaskFactory::characters(const QStringRef &value)
{
    d->lastTextNodeContents = value.toString();
}

void XmlTaskFactory::comment(const QString &/*value*/)
{
}

void XmlTaskFactory::endDocument()
{
}

void XmlTaskFactory::endElement()
{
    qDebug() << "End current element";
    emit leaveCurrentElement();
}

void XmlTaskFactory::endOfSequence()
{
}

void XmlTaskFactory::namespaceBinding(const QXmlName &/*name*/)
{
}

void XmlTaskFactory::processingInstruction(const QXmlName &/*target*/, const QString &/*value*/)
{
}

void XmlTaskFactory::startDocument()
{
}

void XmlTaskFactory::startElement(const QXmlName &name)
{
    QString localname = name.localName(d->query.namePool());
    qDebug() << "Enter element" << localname;
    d->currentElementName = name;
    if (localname == "taskseries") {
        // taskseries is something of a container for a single named task
        // and all the metadata that goes with it. Why it's called a taskseries
        // I've no clue.
        emit enterTaskseriesElement();
    } else if (localname == "tags") {
        emit enterTagsElement();
    } else if (localname == "tag") {
        emit enterTagElement();
    } else if (localname == "participants") {
        emit enterParticipantsElement();
    } else if (localname == "contact") {
        emit enterContactElement();
    } else if (localname == "notes") {
        emit enterNotesElement();
    } else if (localname == "note") {
        emit enterNoteElement();
    } else if (localname == "task") {
        emit enterTaskElement();
    }
}

void XmlTaskFactory::startOfSequence()
{
}

void XmlTaskFactory::startCreateTask()
{
    qDebug() << "startCreateTask";
    Q_ASSERT_X(d->currentTask == 0, "XmlTaskFactory::startCreateTask", "Current task shouldn't exist");
    d->currentTask = new Task(this);
}

void XmlTaskFactory::finishCreateTask()
{
    qDebug() << "finishCreateTask:" << d->currentTask->title();
    Q_ASSERT_X(d->currentTask != 0, "XmlTaskFactory::finishCreateTask", "No current task");
    emit newTask(d->currentTask);
    d->currentTask = 0;
}

void XmlTaskFactory::addTagToCurrentTask()
{
    qDebug() << "Adding tag" << d->lastTextNodeContents << "to task" << d->currentTask->title();
    d->currentTask->addTag(d->lastTextNodeContents);
}
