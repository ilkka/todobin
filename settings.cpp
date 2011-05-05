#include "settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent), m_storage("ilkkalaukkanen", "RTMApp", this)
{
}

QVariant Settings::value(const QString &key) const
{
    return m_storage.value(key);
}

void Settings::setValue(const QString &key, QVariant value)
{
    m_storage.setValue(key, value);
}
