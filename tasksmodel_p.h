#ifndef TASKSMODEL_P_H
#define TASKSMODEL_P_H

#include <QList>

class Task;

class TasksModelPrivate
{
public:
    QList<Task*> tasks;
};

#endif // TASKSMODEL_P_H
