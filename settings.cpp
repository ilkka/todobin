#include "settings.h"

Settings::Settings(QObject *parent) :
    QSettings(parent),
    m_apikey(), m_secret(), m_endpoint()
{
}
