#include "rtminterface.h"
#include "rtminterface_p.h"

#include <QTimer>
#include <QMap>
#include <QCryptographicHash>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDomDocument>
#include <QDomElement>
#include <QtGlobal>

#include "settings.h"

#include <QDebug>

namespace {
const QByteArray APIKEY("0946e2f0273d2ac1c3b16d5e9c6d2a6a");
const QByteArray SECRET("0116088919798a61");
const QUrl ENDPOINT("http://api.rememberthemilk.com/services/rest/");
const QUrl AUTH_URL_BASE("http://www.rememberthemilk.com/services/auth/");
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
    return d->authUrl;
}

void RTMInterface::requestFrob()
{
    QUrl url = apiUrlForMethod("rtm.auth.getFrob");
    qDebug() << "requestFrob with URL" << url.toString();
    d->netSemaphore.acquire();
    d->net->disconnect(SIGNAL(finished(QNetworkReply*)));
    connect(d->net, SIGNAL(finished(QNetworkReply*)), SLOT(handleGetFrobReply(QNetworkReply*)));
    d->net->get(QNetworkRequest(url));
}

void RTMInterface::checkToken(const QString &token)
{
    QueryItems params;
    params << QueryItem("auth_token", token);
    QUrl url = apiUrlForMethod("rtm.auth.checkToken", params);
    qDebug() << "checkToken with URL" << url.toString();
    d->netSemaphore.acquire();
    d->net->disconnect(SIGNAL(finished(QNetworkReply*)));
    connect(d->net, SIGNAL(finished(QNetworkReply*)), SLOT(handleCheckTokenReply(QNetworkReply*)));
    d->net->get(QNetworkRequest(url));
}

void RTMInterface::initialize()
{
    Settings settings;
    QString token = settings.value(Settings::FOURSQUARE_TOKEN).toString();
    if (token.isEmpty()) {
        // no token was stored, we need to authenticate
        requestFrob();
    } else {
        checkToken(token);
    }
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

void RTMInterface::handleGetFrobReply(QNetworkReply *reply)
{
    d->netSemaphore.release();
    ApiReplyParseResult result = parseReply(reply);
    qDebug() << "frobReceived reply:" << result.doc.toString(2);
    if (result.ok) {
        QDomElement frobElement = result.doc.documentElement().firstChildElement("frob");
        d->frob = frobElement.firstChild().toText().data();
        qDebug() << "Got frob" << d->frob;
        updateAuthUrl();
        emit authenticationNeeded(d->authUrl);
    } else {
        qWarning() << "getFrob failed with code"
                   << result.errorCode << ":" << result.errorMsg;
    }
    reply->deleteLater();
}

void RTMInterface::handleCheckTokenReply(QNetworkReply *reply)
{
    d->netSemaphore.release();
    ApiReplyParseResult result = parseReply(reply);
    qDebug() << "checkToken reply:" << result.doc.toString(2);
    if (result.ok) {
        qDebug() << "Token is OK";
    } else {
        qWarning() << "checkToken failed with code"
                   << result.errorCode << ":" << result.errorMsg;
    }
    reply->deleteLater();
}

void RTMInterface::updateAuthUrl()
{
    QUrl url(AUTH_URL_BASE);
    QueryItems items;
    items << QueryItem("api_key", APIKEY)
          << QueryItem("perms", "delete")
          << QueryItem("frob", d->frob);
    items << signQueryParams(items);
    url.setQueryItems(items);
    if (d->authUrl != url) {
        d->authUrl = url;
        qDebug() << "Updated auth URL:" << d->authUrl;
        emit authUrlChanged();
    }
}

RTMInterface::ApiReplyParseResult RTMInterface::parseReply(QIODevice *reply)
{
    ApiReplyParseResult result;
    if (!result.doc.setContent(reply, &result.errorMsg)) {
        qCritical() << "Error parsing API reply:" << result.errorMsg;
        result.ok = false;
    } else {
        QString status = result.doc.documentElement().attribute("stat");
        if (status == "ok") {
            result.ok = true;
        } else if (status == "fail") {
            result.ok = false;
            QDomElement errorElement = result.doc.documentElement().firstChildElement("err");
            result.errorMsg = errorElement.attribute("msg");
            result.errorCode = errorElement.attribute("code");
        } else {
            result.ok = false;
            result.errorCode = "unknown";
            result.errorMsg = QString("Unknown status \"%1\"").arg(status);
        }
    }
    return result;
}

void RTMInterface::handleGetTokenReply(QNetworkReply *reply)
{
    d->netSemaphore.release();
    ApiReplyParseResult result = parseReply(reply);
    qDebug() << "getToken reply:" << result.doc.toString(2);
    if (result.ok) {
        QDomElement authElement = result.doc.documentElement().firstChildElement("auth");
        QDomElement tokenElement = authElement.firstChildElement("token");
        QString token = tokenElement.firstChild().toText().data();
        qDebug() << "Got token" << token;
        Settings settings;
        settings.setValue(Settings::FOURSQUARE_TOKEN, token);
    } else {
        qWarning() << "getToken failed with code"
                   << result.errorCode << ":" << result.errorMsg;
    }
    reply->deleteLater();
}

void RTMInterface::authenticationCompleted()
{
    getToken();
}

void RTMInterface::getToken()
{
    Q_ASSERT_X(!d->frob.isEmpty(), "RTMInterface::authenticationCompleted",
               "Frob cannot be empty at this point");
    QueryItems params;
    params << QueryItem("frob", d->frob);
    QUrl url = apiUrlForMethod("rtm.auth.getToken", params);
    qDebug() << "getToken with URL" << url.toString();
    d->netSemaphore.acquire();
    d->net->disconnect(SIGNAL(finished(QNetworkReply*)));
    connect(d->net, SIGNAL(finished(QNetworkReply*)),
            SLOT(handleGetTokenReply(QNetworkReply*)));
    d->net->get(QNetworkRequest(url));
}

QUrl RTMInterface::apiUrlForMethod(const QString& method,
                                   const QueryItems& extra_params)
{
    QUrl url(ENDPOINT);
    QueryItems items;
    items << QueryItem("api_key", APIKEY)
          << QueryItem("method", method)
          << extra_params;
    items << signQueryParams(items);
    url.setQueryItems(items);
    return url;
}
