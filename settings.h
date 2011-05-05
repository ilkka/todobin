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

    static const QString CFG_KEY_APIKEY;
    static const QString CFG_KEY_SECRET;
    static const QString CFG_KEY_ENDPOINT;

public:
    explicit Settings(QObject *parent = 0);

    Q_INVOKABLE QString apikey() const { return value(CFG_KEY_APIKEY).toString(); }
    Q_INVOKABLE QString secret() const { return value(CFG_KEY_SECRET).toString(); }
    Q_INVOKABLE QUrl endpoint() const { return value(CFG_KEY_ENDPOINT).toUrl(); }

signals:
    void apikeyChanged();
    void secretChanged();
    void endpointChanged();

public slots:
    void setApikey(const QString& apikey) {
        if (apikey != value(CFG_KEY_APIKEY)) {
            setValue(CFG_KEY_APIKEY, apikey);
            emit apikeyChanged();
        }
    }

    void setSecret(const QString& secret) {
        if (secret != value(CFG_KEY_SECRET)) {
            setValue(CFG_KEY_SECRET, secret);
            emit secretChanged();
        }
    }

    void setEndpoint(const QUrl& endpoint) {
        if (endpoint != value(CFG_KEY_ENDPOINT)) {
            setValue(CFG_KEY_ENDPOINT, endpoint);
            emit endpointChanged();
        }
    }
};

#endif // SETTINGS_H
