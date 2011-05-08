#ifndef RTMINTERFACE_P_H
#define RTMINTERFACE_P_H

#include <QNetworkAccessManager>
#include <QSemaphore>
#include <QUrl>

class RTMInterfacePrivate
{
public:
    QNetworkAccessManager* net;
    QSemaphore netSemaphore;

    QString frob;
    QUrl authUrl;
    QString token;
};

#endif // RTMINTERFACE_P_H
