#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QUrl>

class Settings : public QObject
{
    Q_OBJECT

public:
    explicit Settings(QObject *parent = 0);

    /**
     * Get the value of a setting.
     */
    Q_INVOKABLE QVariant value(const QString& key);

    /**
     * Set the value of a setting.
     */
    Q_INVOKABLE void setValue(const QString& key, QVariant value);

    /**
     * Settings key for RTM auth token.
     */
    static const QString RTM_AUTH_TOKEN;

private:
    QSettings m_storage;
};

#endif // SETTINGS_H
