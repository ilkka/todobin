#ifndef RTMINTERFACE_H
#define RTMINTERFACE_H

#include <QObject>
#include <QUrl>
#include <QList>
#include <QPair>

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
     * RTM authentication URL.
     */
    QUrl authUrl();

signals:
    void authUrlChanged();
    void authenticationNeeded();

private slots:
    // For debug only -- kill me
    void dbgDelayLaunch();

    void handleGetFrobReply(QNetworkReply* reply);

private:
    friend class RTMInterfacePrivate;
    RTMInterfacePrivate* const d;

    /**
     * Request frob. Frob will be delivered to frobReceived slot.
     */
    void requestFrob();

    typedef QPair<QString, QString> QueryItem;
    typedef QList<QueryItem> QueryItems;

    /**
     * Sign query according to the rules of the RTM API.
     * Returns an extra QueryItem that is the api_sig parameter.
     * This should be appended to the query.
     */
    QueryItem signQueryParams(const QueryItems& queryItems) const;
};

#endif // RTMINTERFACE_H
