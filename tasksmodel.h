#ifndef TASKSMODEL_H
#define TASKSMODEL_H

#include <QAbstractListModel>

class TasksModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TasksModel(QObject *parent = 0);

signals:

public slots:

};

#endif // TASKSMODEL_H
