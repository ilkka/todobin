#include "tasksmodel.h"
#include "tasksmodel_p.h"
#include "task.h"

TasksModel::TasksModel(QObject *parent) :
    QAbstractListModel(parent), d(new TasksModelPrivate)
{
    // Set roles
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
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
    if (role == TitleRole && orientation == Qt::Horizontal && section == 0) {
        return QVariant("Title");
    }
    return QVariant();
}

QVariant TasksModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == TitleRole) {
        return QVariant(d->tasks.at(index.row())->title());
    }
    return QVariant();
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
