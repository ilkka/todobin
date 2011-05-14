#ifndef DUMMYAPI_H
#define DUMMYAPI_H

#include <QObject>
#include <QUrl>
#include <QTimer>
#include <QFile>
#include <QDebug>

/**
 * This is a "dummy" RTM API implementation that just emits the
 * signals and provides the properties needed for the GUI to work
 * when testing/doing development with static data.
 */
class DummyApi : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl authUrl READ authUrl NOTIFY authUrlChanged)
public:
    explicit DummyApi(bool requireFakeAuth = false, QObject *parent = 0);

    Q_INVOKABLE void initialize() {
        if (m_requireFakeAuth) {
            QTimer::singleShot(1000, this, SIGNAL(authenticationNeeded(QUrl)));
        } else {
            QTimer::singleShot(1000, this, SIGNAL(initializationCompleted()));
        }
    }

    Q_INVOKABLE void authenticationCompleted() {
        QTimer::singleShot(1000, this, SIGNAL(initializationCompleted()));
    }

    QUrl authUrl() { return QUrl("http://www.example.com/fakeapi"); }

signals:
    void authUrlChanged();
    void authenticationNeeded(QUrl authUrl);
    void initializationCompleted();
    void taskListReceived(QIODevice* tasklist);

public slots:
    void requestTaskList() {
        if (!m_fakedata.isOpen() && !m_fakedata.open(QIODevice::ReadOnly)) {
            qCritical() << "Unable to open fake datafile"
                        << m_fakedata.fileName();
        } else {
            emit taskListReceived(&m_fakedata);
        }
    }

    void requestMarkTaskCompleted(const QString& listId,
                                  const QString& seriesId,
                                  const QString& taskId) {

    }

private slots:
    void signalRequireFakeAuth() {
        emit authenticationNeeded(authUrl());
    }

private:
    bool m_requireFakeAuth;
    QFile m_fakedata;
};

#endif // DUMMYAPI_H
