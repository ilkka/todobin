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
        }
    }
    return data;
}

void TasksModel::addTask(Task *t)
{
    beginInsertRows(QModelIndex(), d->tasks.length(), d->tasks.length());
    d->tasks << t;
    endInsertRows();
}

void TasksModel::populate()
{
    emit requestTaskList();
}
