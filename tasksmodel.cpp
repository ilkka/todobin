#include "tasksmodel.h"
#include "tasksmodel_p.h"
#include "task.h"

TasksModel::TasksModel(QObject *parent) :
    QAbstractListModel(parent), d(new TasksModelPrivate)
{
    // Set roles
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[DueRole] = "due";
    roles[TagsRole] = "tags";
    roles[NotesRole] = "notes";
    roles[CompletedRole] = "completed";
    roles[IsCompletedRole] = "isCompleted";
    roles[SeriesIdRole] = "seriesId";
    roles[ListIdRole] = "listId";
    roles[TaskIdRole] = "taskId";
    setRoleNames(roles);
}

TasksModel::~TasksModel()
{
    delete d;
}

int TasksModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return d->tasks.length();
}

QVariant TasksModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant header;
    if (orientation == Qt::Horizontal && section == 0) {
        switch (role) {
        case TitleRole:
            header = "Title";
            break;
        case DueRole:
            header = "Due";
            break;
        case TagsRole:
            header = "Tags";
            break;
        case NotesRole:
            header = "Notes";
            break;
        case CompletedRole:
            header = "Completed";
            break;
        case IsCompletedRole:
            header = "Is completed";
            break;
        case ListIdRole:
            header = "List ID";
            break;
        case SeriesIdRole:
            header = "Series ID";
            break;
        case TaskIdRole:
            header = "Task ID";
            break;
        default:
            break;
        }
    }
    return header;
}

QVariant TasksModel::data(const QModelIndex &index, int role) const
{
    QVariant data;
    if (index.isValid()) {
        Task* t = d->tasks.at(index.row());
        switch (role) {
        case TitleRole:
            data = t->title();
            break;
        case DueRole:
            data = t->due().toString(Qt::TextDate);
            break;
        case TagsRole:
            data = t->tags().join(", ");
            break;
        case NotesRole:
            data = t->notes();
            break;
        case CompletedRole:
            data = t->completed();
            break;
        case IsCompletedRole:
            data = t->isCompleted();
            break;
        case ListIdRole:
            data = t->listId();
            break;
        case SeriesIdRole:
            data = t->seriesId();
            break;
        case TaskIdRole:
            data = t->taskId();
            break;
        }
    }
    return data;
}

void TasksModel::addTask(Task *t)
{
    QModelIndex index = indexForTask(t->listId(), t->seriesId(), t->taskId());
    if (index.isValid()) {
        Task* old = d->tasks.at(index.row());
        old->setCompleted(t->completed());
        old->setTitle(t->title());
        old->setTags(t->tags());
        old->setNotes(t->notes());
        old->setDue(t->due());
        old->setPriority(t->priority());
        emit dataChanged(index, index);
        t->deleteLater();
    } else {
        beginInsertRows(QModelIndex(), d->tasks.length(), d->tasks.length());
        d->tasks << t;
        endInsertRows();
    }
}

void TasksModel::populate()
{
    emit requestTaskList();
}

void TasksModel::setTaskCompleted(int index, bool completed)
{
    Task* t = d->tasks.at(index);
    if (!t->isCompleted() == completed) {
        t->setCompleted(QDateTime::currentDateTimeUtc());
        emit dataChanged(createIndex(0, index), createIndex(0, index));
    }
}

QModelIndex TasksModel::indexForTask(const QString &listId, const QString &seriesId, const QString &taskId)
{
    for (int idx = 0; idx < d->tasks.length(); ++idx) {
        Task* t = d->tasks.at(idx);
        if (t->listId() == listId && t->seriesId() == seriesId && t->taskId() == taskId) {
            return index(idx);
        }
    }
    return QModelIndex();
}

bool TasksModel::hasTask(const QString &listId, const QString &seriesId, const QString &taskId)
{
    return indexForTask(listId, seriesId, taskId).isValid();
}
