#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QDateTime>
#include <QStringList>

class Task : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QDateTime due READ due WRITE setDue NOTIFY dueChanged)
    Q_PROPERTY(QStringList tags READ tags WRITE setTags NOTIFY tagsChanged)
public:
    explicit Task(QObject *parent = 0);

    Q_INVOKABLE void addTag(const QString& tag) {
        if (!m_tags.contains(tag)) {
            m_tags << tag;
            emit tagsChanged();
        }
    }

    // getters
    const QString& title() const { return m_title; }
    const QDateTime& due() const { return m_due; }
    const QStringList& tags() const { return m_tags; }

    // setters
    void setTitle(const QString& title) {
        if (title != m_title) {
            m_title = title;
            emit titleChanged();
        }
    }
    void setDue(const QDateTime& due) {
        if (m_due != due) {
            m_due = due;
            emit dueChanged();
        }
    }
    void setTags(const QStringList& tags) {
        if (m_tags != tags) {
            m_tags = tags;
            emit tagsChanged();
        }
    }

signals:
    void titleChanged();
    void dueChanged();
    void tagsChanged();

private:
    QString m_title;
    QDateTime m_due;
    QStringList m_tags;
};

#endif // TASK_H
