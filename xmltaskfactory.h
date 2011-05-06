#ifndef XMLTASKFACTORY_H
#define XMLTASKFACTORY_H

#include <QAbstractXmlReceiver>

class Task;

class XmlTaskFactoryPrivate;

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

private:
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

    friend class XmlTaskFactoryPrivate;
    XmlTaskFactoryPrivate* const d;
};

#endif // XMLTASKFACTORY_H
