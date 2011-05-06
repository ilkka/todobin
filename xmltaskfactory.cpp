#include "xmltaskfactory.h"
#include "xmltaskfactory_p.h"

#include <QDebug>

XmlTaskFactory::XmlTaskFactory(QIODevice *source, QObject *parent) :
    QObject(parent), QAbstractXmlReceiver(), d(new XmlTaskFactoryPrivate), m_state(AtRoot)
{
    // Build statemachine:
    QState *root = new QState();
    QState *in_taskseries = new QState();
    QState *in_tags = new QState();
    QState *in_tag = new QState();
    root->addTransition(this, SIGNAL(enterTaskseriesElement()), in_taskseries);
    in_taskseries->addTransition(this, SIGNAL(enterTagsElement()), in_tags);
    in_taskseries->assignProperty(this, "state", InTaskseries);
    in_tags->addTransition(this, SIGNAL(enterTagElement()), in_tag);
    in_tags->assignProperty(this, "state", InTags);
    in_tag->addTransition(this, SIGNAL(leaveTagElement()), in_tag);
    in_tag->assignProperty(this, "state", InTag);
    in_tags->addTransition(this, SIGNAL(leaveTagsElement()), in_taskseries);
    in_taskseries->addTransition(this, SIGNAL(leaveTaskseriesElement()), root);
    d->sm.addState(root);
    d->sm.addState(in_taskseries);
    d->sm.addState(in_tags);
    d->sm.addState(in_tag);
    d->sm.setInitialState(root);
    d->sm.start();

    // Build and evaluate query
    d->query.bindVariable("input", source);
    d->query.setQuery("doc($input)/rsp/tasks/list/taskseries");
    d->query.evaluateTo(this);
}

XmlTaskFactory::~XmlTaskFactory()
{
    delete d;
}

QList<Task*> XmlTaskFactory::tasks() const
{
    return d->tasks;
}

void XmlTaskFactory::atomicValue(const QVariant &/*value*/)
{
}

void XmlTaskFactory::attribute(const QXmlName &/*name*/, const QStringRef &/*value*/)
{
}

void XmlTaskFactory::characters(const QStringRef &/*value*/)
{
}

void XmlTaskFactory::comment(const QString &/*value*/)
{
}

void XmlTaskFactory::endDocument()
{
    if (d->currentTask != 0) {
        d->tasks << d->currentTask;
        d->currentTask = 0;
    }
}

void XmlTaskFactory::endElement()
{
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
    qDebug() << "Hit element" << localname;
    if (localname == "taskseries") {
        // taskseries is something of a container for a single named task
        // and all the metadata that goes with it. Why it's called a taskseries
        // I've no clue.
        if (d->currentTask != 0) {
            d->tasks << d->currentTask;
            d->currentTask = new Task();
        }
    }
}

void XmlTaskFactory::startOfSequence()
{
}

XmlTaskFactory::FactoryState XmlTaskFactory::state() const
{
    return d->state;
}
