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

private slots:

    // API reply handlers for methods
    void handleGetFrobReply(QNetworkReply* reply);
    void handleCheckTokenReply(QNetworkReply* reply);
    void handleGetTokenReply(QNetworkReply* reply);

    /**
     * Update auth URL after e.g. frob has changed.
     */
    void updateAuthUrl();

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
    void checkToken(const QString& token);

    /**
     * Get authentication token from RTM.
     */
    void getToken();

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
