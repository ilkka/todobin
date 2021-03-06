#ifndef XMLTASKFACTORY_H
#define XMLTASKFACTORY_H

#include <QAbstractXmlReceiver>
#include <QDomDocument>

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
public:
    explicit XmlTaskFactory(QObject *parent = 0);
    virtual ~XmlTaskFactory();

public slots:
    /**
     * Parse an XML task list.
     * This will cause the factory to start emitting tasks so make
     * sure something's connected to XmlTaskFactory::newTask.
     * @param source IO device for reading XML from.
     */
    void parseTaskList(QIODevice *source);

signals:
    /**
     * Emitted when a Task has been created.
     * @param task the newly-created Task instance.
     */
    void newTask(Task* task);

    // For internal use.
    void enterTaskseriesElement();
    void enterTagsElement();
    void enterTagElement();
    void enterParticipantsElement();
    void enterContactElement();
    void enterNotesElement();
    void enterNoteElement();
    void enterTaskElement();
    void leaveCurrentElement();

private slots:
    void startCreateTask();
    void finishCreateTask();
    void addNoteToCurrentTask();
    void addTagToCurrentTask();

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

    void handleDueAttribute(const QString& value);
    void handleCompletedAttribute(const QString& value);
    void handlePriorityAttribute(const QString& value);

    // Parse an RTM timestamp
    QDateTime parseTimestamp(const QString& stamp) const;

    friend class XmlTaskFactoryPrivate;
    XmlTaskFactoryPrivate* const d;
};

#endif // XMLTASKFACTORY_H
