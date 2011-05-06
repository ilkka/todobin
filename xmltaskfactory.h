#ifndef XMLTASKFACTORY_H
#define XMLTASKFACTORY_H

#include <QAbstractXmlReceiver>

class Task;

class XmlTaskFactoryPrivate;

/**
 * Use this class to create tasks from RTM task XML.
 * The idea is to create an instance of this class, give it RTM XML
 * and extract the tasks.
 *
 * @note it is the caller's responsibility to free the tasks!
 */
class XmlTaskFactory : public QObject, QAbstractXmlReceiver
{
    Q_OBJECT
    Q_ENUMS(FactoryState)
    Q_PROPERTY(FactoryState state READ state WRITE setState NOTIFY stateChanged)
public:
    explicit XmlTaskFactory(QIODevice *source, QObject *parent = 0);
    virtual ~XmlTaskFactory();

    /**
     * Get the tasks constructed by this factory.
     * @return a list of tasks.
     * @note it is the caller's responsibility to free the tasks!
     */
    QList<Task*> tasks() const;

signals:
    void enterTaskseriesElement();
    void leaveTaskseriesElement();
    void enterTagsElement();
    void leaveTagsElement();
    void enterTagElement();
    void leaveTagElement();

    void stateChanged();

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

    /**
     * Enumerated type for tracking factory state. For internal use.
     */
    enum FactoryState {
        AtRoot, InTaskseries, InTags, InTag
    };

    /**
     * Get current factory state.
     */
    FactoryState state() const { return m_state; }

    /**
     * Set current factory state.
     */
    void setState(FactoryState state) {
        if (state != m_state) {
            m_state = state;
            emit stateChanged();
        }
    }

    FactoryState m_state;
};

#endif // XMLTASKFACTORY_H
