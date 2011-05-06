#include "xmltaskfactory.h"

#include <QDebug>

XmlTaskFactory::XmlTaskFactory(QIODevice *source, QObject *parent) :
    QObject(parent), QAbstractXmlReceiver(), m_query()
{
    // Build and evaluate query
    m_query.bindVariable("input", source);
    m_query.setQuery("doc($input)/rsp/tasks/list/taskseries");
    m_query.evaluateTo(this);
}

QList<Task*> XmlTaskFactory::tasks() const
{
    return m_tasks;
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

