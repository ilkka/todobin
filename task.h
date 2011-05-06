#ifndef TASK_H
#define TASK_H

#include <QObject>

class Task : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
public:
    explicit Task(QObject *parent = 0);

    // getters
    const QString& title() const { return m_title; }

    // setters
    void setTitle(const QString& title) {
        if (title != m_title) {
            m_title = title;
            emit titleChanged();
        }
    }

signals:
    void titleChanged();

private:
    QString m_title;

};

#endif // TASK_H
