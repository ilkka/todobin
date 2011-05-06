#include "tasksmodel.h"
#include "tasksmodel_p.h"

#include <QFile>

TasksModel::TasksModel(QObject *parent) :
    QAbstractListModel(parent), d(new TasksModelPrivate)
{
    d->doc = new QDomDocument;
    QFile f("qml/RTMApp/dummydata/all_tasks_response.xml");
    if (!f.open(QIODevice::ReadOnly)) {
        throw "Can't open XML file";
    } else if(!d->doc->setContent(&file)) {
        throw "Can't set document content";
    }
    f.close();
}

TasksModel::~TasksModel()
{
    delete d;
}

int TasksModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant TasksModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QVariant TasksModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}
