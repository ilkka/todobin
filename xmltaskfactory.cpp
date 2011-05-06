#include "xmltaskfactory.h"
#include "xmltaskfactory_p.h"

#include <QDebug>

XmlTaskFactory::XmlTaskFactory(QIODevice *source, QObject *parent) :
    QObject(parent), QAbstractXmlReceiver(), d(new XmlTaskFactoryPrivate)
{
    // Build and evaluate query
    d->query.bindVariable("input", source);
    d->query.setQuery("doc($input)/rsp/tasks/list/taskseries");
    d->query.evaluateTo(this);
}

QList<Task*> XmlTaskFactory::tasks() const
{
    return d->tasks;
}

void XmlTaskFactory::atomicValue(const QVariant &value)
{
}

void XmlTaskFactory::attribute(const QXmlName &name, const QStringRef &value)
{
}

void XmlTaskFactory::characters(const QStringRef &value)
{
}

void XmlTaskFactory::comment(const QString &value)
{
}

void XmlTaskFactory::endDocument()
{
}

void XmlTaskFactory::endElement()
{
}

void XmlTaskFactory::endOfSequence()
{
}

void XmlTaskFactory::namespaceBinding(const QXmlName &name)
{
}

void XmlTaskFactory::processingInstruction(const QXmlName &target, const QString &value)
{
}

void XmlTaskFactory::startDocument()
{
}

void XmlTaskFactory::startElement(const QXmlName &name)
{
    qDebug() << "Hit element" << name.localName(m_query.namePool());
}

void XmlTaskFactory::startOfSequence()
{
}

