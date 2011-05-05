#include "settings.h"

Settings::Settings(QObject *parent) :
    QSettings("ilkkalaukkanen", "RTMApp", parent),
    m_apikey(), m_secret(), m_endpoint()
{
}
