#include "tasksmodel.h"
#include "tasksmodel_p.h"

#include <QFile>

TasksModel::TasksModel(QObject *parent) :
    QAbstractListModel(parent), d(new TasksModelPrivate)
{
    // Read dummydata doc
    d->doc = new QDomDocument;
    QFile f("qml/RTMApp/dummydata/all_tasks_response.xml");
    if (!f.open(QIODevice::ReadOnly)) {
        throw "Can't open XML file";
    } else if(!d->doc->setContent(&file)) {
        throw "Can't set document content";
    }
    f.close();

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
    return 1;
}

QVariant TasksModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QVariant TasksModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}
