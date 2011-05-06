#include "xmltaskfactory.h"

#include <QXmlQuery>

XmlTaskFactory::XmlTaskFactory(QIODevice *source, QObject *parent) :
    QAbstractXmlReceiver(parent)
{
    // Build and evaluate query
    QXmlQuery query;
    query.bindVariable("input", source);
    query.setQuery("doc($input)/rsp/tasks/list/taskseries");
    query.evaluateTo(this);
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
}

void XmlTaskFactory::startOfSequence()
{
}

