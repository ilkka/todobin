#ifndef XMLTASKFACTORY_H
#define XMLTASKFACTORY_H

#include <QAbstractXmlReceiver>
#include <QList>

class Task;

/**
 * Use this class to create tasks from RTM task XML.
 * The idea is to create an instance of this class, give it RTM XML
 * and extract the tasks.
 */
class XmlTaskFactory : public QObject, QAbstractXmlReceiver
{
    Q_OBJECT
public:
    explicit XmlTaskFactory(QIODevice *source, QObject *parent = 0);

    QList<Task*> tasks() const;

    // implemented abstract methods from QAbstractXmlReceiver
    void atomicValue(const QVariant &value);
    void attribute(const QXmlName &name, const QStringRef &value);
    void characters(const QStringRef &value);
    void comment(const QString &value);
    void endDocument();
    void endElement();
    void endOfSequence();
    void namespaceBinding(const QXmlName &name);
    void processingInstruction(const QXmlName &target, const QString &value);
    void startDocument();
    void startElement(const QXmlName &name);
    void startOfSequence();

private:
    QList<Task*> m_tasks;
};

#endif // XMLTASKFACTORY_H
