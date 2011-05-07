#include "rtminterface.h"
#include "rtminterface_p.h"

#include <QTimer>
#include <QMap>
#include <QCryptographicHash>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDomDocument>
#include <QDomElement>

#include <QDebug>

namespace {
const QByteArray APIKEY("0946e2f0273d2ac1c3b16d5e9c6d2a6a");
const QByteArray SECRET("0116088919798a61");
const QUrl ENDPOINT("http://api.rememberthemilk.com/services/rest/");
}

RTMInterface::RTMInterface(QObject *parent) :
    QObject(parent), d(new RTMInterfacePrivate)
{
    d->net = new QNetworkAccessManager(this);
    d->netSemaphore.release();
}

RTMInterface::~RTMInterface()
{
    delete d;
}

QUrl RTMInterface::authUrl()
{
    QUrl url("http://dummy.auth.url");
    return url;
}

void RTMInterface::requestFrob()
{
    QUrl url(ENDPOINT);
    QueryItems items;
    items << QueryItem("api_key", APIKEY);
    items << QueryItem("method", "rtm.auth.getFrob");
    items << signQueryParams(items);
    url.setQueryItems(items);
    qDebug() << "requestFrob with URL" << url.toString();
    d->netSemaphore.acquire();
    d->net->disconnect(SIGNAL(finished(QNetworkReply*)));
    connect(d->net, SIGNAL(finished(QNetworkReply*)), SLOT(frobReceived(QNetworkReply*)));
    d->net->get(QNetworkRequest(url));
}

void RTMInterface::initialize()
{
    requestFrob();
}

void RTMInterface::dbgDelayLaunch()
{
    emit authenticationNeeded();
}

RTMInterface::QueryItem RTMInterface::signQueryParams(const QueryItems &queryItems) const
{
    // the signature is the md5 of our secret, concatenated with
    // all the query keys and items in alphabetical order.
    QMap<QString, QString> sortedItems;
    Q_FOREACH(const QueryItem& item, queryItems) {
        sortedItems[item.first] = item.second;
    }
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(SECRET);
    Q_FOREACH(const QString& key, sortedItems.keys()) {
        hash.addData(key.toUtf8());
        hash.addData(sortedItems[key].toUtf8());
    }
    return QueryItem("api_sig", hash.result().toHex());
}

void RTMInterface::frobReceived(QNetworkReply *reply)
{
    d->netSemaphore.release();
    QDomDocument doc;
    QString errorMsg;
    int errorLine;
    int errorColumn;
    if (!doc.setContent(reply, &errorMsg, &errorLine, &errorColumn)) {
        qCritical() << "Error parsing getFrob reply:"
                    << errorMsg << "at line" << errorLine
                    << "col" << errorColumn;
    } else {
        qDebug() << "frobReceived reply:" << doc.toString(2);
        QString status = doc.documentElement().attribute("stat");
        if (status == "ok") {
            QDomElement frobElement = doc.documentElement().firstChildElement("frob");
            d->frob = frobElement.firstChild().toText().data();
            qDebug() << "Got frob" << d->frob;
        } else if (status == "fail"){
            QDomElement errorElement = doc.documentElement().firstChildElement("err");
            QString errorMsg = errorElement.attribute("msg");
            QString errorCode = errorElement.attribute("code");
            qWarning() << "getFrob failed with code" << errorCode << ":" << errorMsg;
        } else {
            qWarning() << "Unknown status" << status;
        }
    }
    reply->deleteLater();
}
