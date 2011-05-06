#include "tasksmodel.h"
#include "tasksmodel_p.h"
#include "xmltaskfactory.h"

#include <QFile>

TasksModel::TasksModel(QObject *parent) :
    QAbstractListModel(parent), d(new TasksModelPrivate)
{
    // Open dummydata file
    QFile f("qml/RTMApp/dummydata/all_tasks_response.xml");
    if (!f.open(QIODevice::ReadOnly)) {
        throw "Can't open XML file";
    }
    XmlTaskFactory factory(&f);
    d->tasks = factory.tasks();

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
    return 5;
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
        return QVariant(QString("Moro %1").arg(index.row()));
    }
    return QVariant();
}
