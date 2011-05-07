#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QUrl>

class Settings : public QObject
{
    Q_OBJECT

public:
    explicit Settings(QObject *parent = 0);

    Q_INVOKABLE QVariant value(const QString& key);
    Q_INVOKABLE void setValue(const QString& key, QVariant value);

private:
    QSettings m_storage;
};

#endif // SETTINGS_H
