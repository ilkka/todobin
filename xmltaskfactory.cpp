#include "xmltaskfactory.h"
#include "xmltaskfactory_p.h"

#include <QDebug>

XmlTaskFactory::XmlTaskFactory(QIODevice *source, QObject *parent) :
    QObject(parent), QAbstractXmlReceiver(), d(new XmlTaskFactoryPrivate)
{
    // Build statemachine:
    QState *root = new QState();
    QState *in_taskseries = new QState();
    QState *in_tags = new QState();
    QState *in_tag = new QState();
    root->addTransition(this, SIGNAL(enterTaskseriesElement()), in_taskseries);
    in_taskseries->addTransition(this, SIGNAL(enterTagsElement()), in_tags);
    in_tags->addTransition(this, SIGNAL(enterTagElement()), in_tag);
    in_tag->addTransition(this, SIGNAL(leaveTagElement()), in_tag);
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

void XmlTaskFactory::characters(const QStringRef &value)
{
    d->currentStringRef = value;
}

void XmlTaskFactory::comment(const QString &/*value*/)
{
}

void XmlTaskFactory::endDocument()
{
}

void XmlTaskFactory::endElement()
{
    QString localname = d->currentElementName.localName(d->query.namePool());
    qDebug() << "Leave element" << localname;
    if (localname == "taskseries") {
        emit leaveTaskseriesElement();
    }
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
    }
}

void XmlTaskFactory::startOfSequence()
{
}

void XmlTaskFactory::startCreateTask()
{
    assert(d->currentTask == 0);
    d->currentTask = new Task();
}

void XmlTaskFactory::finishCreateTask()
{
    assert(d->currentTask != 0);
    d->tasks << d->currentTask;
    d->currentTask = 0;
}

void XmlTaskFactory::addTagToCurrentTask()
{

}
