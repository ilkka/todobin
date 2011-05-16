#ifndef RTMINTERFACE_H
#define RTMINTERFACE_H

#include <QObject>
#include <QUrl>
#include <QList>
#include <QPair>
#include <QDomDocument>

class RTMInterfacePrivate;
class QNetworkReply;

class RTMInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl authUrl READ authUrl NOTIFY authUrlChanged)
public:
    explicit RTMInterface(QObject *parent = 0);
    virtual ~RTMInterface();

    /**
     * Initialize API. Call after signal handlers for all the API
     * signals are registered.
     */
    Q_INVOKABLE void initialize();

    /**
     * Called when user has completed browser authentication.
     * We can now get an auth token using our stored frob.
     */
    Q_INVOKABLE void authenticationCompleted();

    /**
     * RTM authentication URL.
     */
    QUrl authUrl();

signals:
    /**
     * Emitted if the auth URL changes. In practice it only
     * changes when we're unauthenticated and receive a frob.
     */
    void authUrlChanged();

    /**
     * The user has to authenticate using a browser before
     * we can continue. The signal handler should display
     * the URL given as parameter, and call authenticationCompleted()
     * when the process is finished.
     */
    void authenticationNeeded(QUrl authUrl);

    /**
     * API initialization is complete and requests can be
     * issued to API methods.
     */
    void initializationCompleted();

    /**
     * Task list has been received from the API.
     * @param tasklist the XML reply with the tasks.
     */
    void taskListReceived(QIODevice* tasklist);

    /**
     * RTM has given us a timeline. This is mostly for internal use,
     * to enable RTMInterface to queue requests. When it needs to modify
     * a task but doesn't yet have a timeline, it requests a timeline
     * and temporarily connects to this signal with a slot that will
     * retry the original task modification.
     */
    void timelineReceived();

public slots:
    /**
     * Get task list from RTM.
     */
    void requestTaskList();

    /**
     * Request RTM to mark task as completed.
     */
    void requestMarkTaskCompleted(const QString& listId, const QString& seriesId, const QString& taskId);

private slots:

    // API reply handlers for methods
    void handleGetFrobReply(QNetworkReply* reply);
    void handleCheckTokenReply(QNetworkReply* reply);
    void handleGetTokenReply(QNetworkReply* reply);
    void handleTaskListReply(QNetworkReply* reply);
    void handleTimelineReply(QNetworkReply* reply);
    void handleTaskModificationReply(QNetworkReply* reply);

    /**
     * Update auth URL after e.g. frob has changed.
     */
    void updateAuthUrl();

    /**
     * Perform pending modification. Used to e.g. finish a task complete
     * operation that first needed to fetch a timeline.
     */
    void performPendingModification();

private:
    friend class RTMInterfacePrivate;
    RTMInterfacePrivate* const d;

    /**
     * Exception class representing an API reply parse error.
     */
    class ParseError {};

    /**
     * Request frob. Frob will be delivered to handleGetFrobReply slot.
     */
    void requestFrob();

    /**
     * Check validity of auth token. Reply will be delivered to
     * handleCheckTokenReply slot.
     */
    void checkToken();

    /**
     * Get authentication token from RTM.
     */
    void requestToken();

    /**
     * Request a timeline from RTM.
     */
    void requestTimeline();

    typedef QPair<QString, QString> QueryItem;
    typedef QList<QueryItem> QueryItems;

    /**
     * Sign query according to the rules of the RTM API.
     * Returns an extra QueryItem that is the api_sig parameter.
     * This should be appended to the query.
     */
    QueryItem signQueryParams(const QueryItems& queryItems) const;

    /**
     * Generate a signed API url for the given method
     * and the given parameters.
     * @param method the name of the method.
     * @param extra_params the list of method-specific parameters.
     * @return a signed API url.
     */
    QUrl apiUrlForMethod(const QString& method,
                         const QueryItems& extra_params = QueryItems());

    /**
     * Struct for holding the result of an API reply parse attempt.
     */
    struct ApiReplyParseResult {
        bool ok;
        QString errorCode;
        QString errorMsg;
        QDomDocument doc;
    };

    /**
     * Parse a RTM API network reply and return DOM document.
     */
    ApiReplyParseResult parseReply(QIODevice* reply);

};

#endif // RTMINTERFACE_H
