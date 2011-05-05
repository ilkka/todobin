#include "settings.h"

Settings::Settings(QObject *parent) :
    QSettings("ilkkalaukkanen", "RTMApp", parent)
{
}

const QString Settings::CFG_KEY_APIKEY = "foursquare/apikey";
const QString Settings::CFG_KEY_SECRET = "foursquare/secret";
const QString Settings::CFG_KEY_ENDPOINT = "foursquare/endpoint";
