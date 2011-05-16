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
    // leaving note adds the last seen text node as a note to the current task
    connect(in_note, SIGNAL(exited()), SLOT(addNoteToCurrentTask()));
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
    d->query.setQuery("doc($input)//list/taskseries");
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
    if (nodeName == "taskseries") {
        if (attributeName == "name") {
            Q_ASSERT_X(d->currentTask != 0, "XmlTaskFactory::attribute", "No current task");
            d->currentTask->setTitle(value.toString());
            qDebug() << "Set current task title to" << value.toString();
        } else if (attributeName == "id"){
            Q_ASSERT_X(d->currentTask != 0, "XmlTaskFactory::attribute", "No current task");
            d->currentTask->setSeriesId(value.toString());
            qDebug() << "Set current task series ID to" << value.toString();
        }
    } else if (nodeName == "task") {
        if (attributeName == "due") {
            handleDueAttribute(value.toString());
        } else if (attributeName == "completed") {
            handleCompletedAttribute(value.toString());
        } else if (attributeName == "priority") {
            handlePriorityAttribute(value.toString());
        } else if (attributeName == "id") {
            Q_ASSERT_X(d->currentTask != 0, "XmlTaskFactory::attribute", "No current task");
            d->currentTask->setTaskId(value.toString());
            qDebug() << "Set current task ID to" << value.toString();
        }
    } else if (nodeName == "note") {
        if (attributeName == "title") {
            d->lastNoteTitle = value.toString();
        }
    }
}

void XmlTaskFactory::handleDueAttribute(const QString& value)
{
    Q_ASSERT_X(d->currentTask != 0, "XmlTaskFactory::handleDueAttribute", "No current task");
    QString stamp = value.trimmed();
    if (!stamp.isEmpty()) {
        QDateTime due = parseTimestamp(stamp);
        if (due.isValid()) {
            d->currentTask->setDue(due);
            qDebug() << "Set current task due to"
                     << due.toString();
        }
    }
}

void XmlTaskFactory::handleCompletedAttribute(const QString &value)
{
    Q_ASSERT_X(d->currentTask != 0, "XmlTaskFactory::handleCompletedAttribute", "No current task");
    QString stamp = value.trimmed();
    if (!stamp.isEmpty()) {
        QDateTime completed = parseTimestamp(stamp);
        if (completed.isValid()) {
            d->currentTask->setCompleted(completed);
            qDebug() << "Set current task completion to"
                     << completed.toString();
        }
    }
}

void XmlTaskFactory::handlePriorityAttribute(const QString &value)
{
    Q_ASSERT_X(d->currentTask != 0, "XmlTaskFactory::handlePriorityAttribute", "No current task");
    QString priority = value.trimmed();
    if (priority == "1") {
        d->currentTask->setPriority(Task::PRIO_FIRST);
    } else if (priority == "2") {
        d->currentTask->setPriority(Task::PRIO_SECOND);
    } else if (priority == "3") {
        d->currentTask->setPriority(Task::PRIO_THIRD);
    } else {
        d->currentTask->setPriority(Task::PRIO_NONE);
    }
    qDebug() << "Set current task priority to" << d->currentTask->priority();
}

QDateTime XmlTaskFactory::parseTimestamp(const QString& stamp) const
{
    // RTM returns all timestamps in UTC but QDateTime
    // can't parse the trailing "Z" from the RFC-3339 notation,
    // so we explicitly set the QDateTime to UTC and chop off the
    // "Z"
    QDateTime dt = QDateTime::fromString(stamp.left(stamp.length() - 1), Qt::ISODate);
    dt.setTimeSpec(Qt::UTC);
    return dt;
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
        // Clear out the text node holder so we *know* it came
        // from this tag if not empty.
        d->lastTextNodeContents = "";
        emit enterTagElement();
    } else if (localname == "participants") {
        emit enterParticipantsElement();
    } else if (localname == "contact") {
        emit enterContactElement();
    } else if (localname == "notes") {
        emit enterNotesElement();
    } else if (localname == "note") {
        // Same as for tag, make sure the note text comes from
        // this element
        d->lastTextNodeContents = "";
        // also forget the title
        d->lastNoteTitle = "";
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
    Q_ASSERT_X(d->currentTask != 0, "XmlTaskFactory::addTagToCurrentTask", "No current task");
    qDebug() << "Adding tag" << d->lastTextNodeContents << "to task" << d->currentTask->title();
    d->currentTask->addTag(d->lastTextNodeContents);
}

void XmlTaskFactory::addNoteToCurrentTask()
{
    Q_ASSERT_X(d->currentTask != 0, "XmlTaskFactory::addNoteToCurrentTask", "No current task");
    if (!d->lastTextNodeContents.isEmpty()) {
        qDebug() << "Adding note" << d->lastNoteTitle << "to task" << d->currentTask->title();
        // Change newlines to HTML breaks:
        d->lastTextNodeContents.replace('\n', "<br/>");
        if (!d->lastNoteTitle.isEmpty()) {
            d->currentTask->addNote(QString("<b>%1</b><br/>%2").arg(d->lastNoteTitle, d->lastTextNodeContents));
        } else {
            d->currentTask->addNote(d->lastTextNodeContents);
        }
    } else {
        qDebug() << "Refusing to add an empty note";
    }
}
