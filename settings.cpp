#include "settings.h"

const QString Settings::RTM_AUTH_TOKEN("foursquare/token");

Settings::Settings(QObject *parent) :
    QObject(parent), m_storage("ilkkalaukkanen", "todobin", this)
{
}

QVariant Settings::value(const QString &key)
{
    m_storage.sync();
    return m_storage.value(key);
}

void Settings::setValue(const QString &key, QVariant value)
{
    m_storage.setValue(key, value);
    m_storage.sync();
}
