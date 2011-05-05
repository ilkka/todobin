#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QUrl>

class Settings : public QSettings
{
    Q_OBJECT
    Q_PROPERTY(QString apikey READ apikey WRITE setApikey NOTIFY apikeyChanged)
    Q_PROPERTY(QString secret READ secret WRITE setSecret NOTIFY secretChanged)
    Q_PROPERTY(QUrl endpoint READ endpoint WRITE setEndpoint NOTIFY endpointChanged)

public:
    explicit Settings(QObject *parent = 0);

    Q_INVOKABLE const QString& apikey() const { return m_apikey; }
    Q_INVOKABLE const QString& secret() const { return m_secret; }
    Q_INVOKABLE const QUrl& endpoint() const { return m_endpoint; }

signals:
    void apikeyChanged();
    void secretChanged();
    void endpointChanged();

public slots:
    void setApikey(const QString& apikey) {
        if (apikey != m_apikey) {
            m_apikey = apikey;
            emit apikeyChanged();
        }
    }

    void setSecret(const QString& secret) {
        if (secret != m_secret) {
            m_secret = secret;
            emit secretChanged();
        }
    }

    void setEndpoint(const QUrl& endpoint) {
        if (endpoint != m_endpoint) {
            m_endpoint = endpoint;
            emit endpointChanged();
        }
    }

private:
    QString m_apikey;
    QString m_secret;
    QUrl m_endpoint;
};

#endif // SETTINGS_H
