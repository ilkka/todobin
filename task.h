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
    Q_ENUMS(Priority)
    Q_PROPERTY(Priority priority READ priority WRITE setPriority NOTIFY priorityChanged)
    Q_PROPERTY(QDateTime completed READ completed NOTIFY completedChanged)
    Q_PROPERTY(bool isCompleted READ isCompleted NOTIFY isCompletedChanged)
public:
    // valid task priorities
    enum Priority {
        PRIO_NONE,
        PRIO_FIRST,
        PRIO_SECOND,
        PRIO_THIRD
    };

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
    Priority priority() const { return m_priority; }
    const QDateTime& completed() const { return m_completed; }
    bool isCompleted() const { return m_completed.isValid(); }

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
    void setPriority(Priority priority) {
        if (m_priority != priority) {
            m_priority = priority;
            emit priorityChanged();
        }
    }
    void setCompleted(const QDateTime& completed) {
        if (m_completed != completed) {
            bool changes = (m_completed.isValid() != completed.isValid());
            m_completed = completed;
            emit completedChanged();
            if (changes) {
                emit isCompletedChanged();
            }
        }
    }

signals:
    void titleChanged();
    void dueChanged();
    void tagsChanged();
    void priorityChanged();
    void completedChanged();
    void isCompletedChanged();

private:
    QString m_title;
    QDateTime m_due;
    QStringList m_tags;
    Priority m_priority;
    QDateTime m_completed;
};

#endif // TASK_H
