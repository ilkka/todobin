#ifndef RTMINTERFACE_P_H
#define RTMINTERFACE_P_H

#include <QNetworkAccessManager>
#include <QSemaphore>

class RTMInterfacePrivate
{
public:
    QNetworkAccessManager* net;
    QSemaphore netSemaphore;
    QString frob;
};

#endif // RTMINTERFACE_P_H