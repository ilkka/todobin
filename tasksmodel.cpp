#include "tasksmodel.h"
#include "tasksmodel_p.h"

#include <QFile>
#include <QXmlQuery>
#include <QXmlResultItems>

TasksModel::TasksModel(QObject *parent) :
    QAbstractListModel(parent), d(new TasksModelPrivate)
{
    // Open dummydata file
    QFile f("qml/RTMApp/dummydata/all_tasks_response.xml");
    if (!f.open(QIODevice::ReadOnly)) {
        throw "Can't open XML file";
    }

    // Build and evaluate query
    QXmlQuery query;
    query.bindVariable("input", &f);
    query.setQuery("doc($input)/rsp/tasks/list/taskseries/@name/string()");
    QXmlResultItems result;
    query.evaluateTo(&result);

    // Put the results in the model
    QXmlItem item(result.next());
    while (!item.isNull()) {
        d->result << item.toAtomicValue().toString();
        item = result.next();
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
    return d->result.length();
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
        return d->result.at(index.row());
    }
    return QVariant();
}
