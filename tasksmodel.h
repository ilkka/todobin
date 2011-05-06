#ifndef TASKSMODEL_H
#define TASKSMODEL_H

#include <QAbstractListModel>

class TasksModelPrivate;

class Task;

class TasksModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TaskRoles {
        TitleRole = Qt::UserRole + 1
    };

    explicit TasksModel(QObject *parent = 0);
    virtual ~TasksModel();

    /** @see QAbstractListModel::rowCount
      */
    int rowCount(const QModelIndex &parent) const;

    /** @see QAbstractListModel::data
      */
    QVariant data(const QModelIndex &index, int role) const;

    /** @see QAbstractListModel::headerData
      */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public slots:
    /**
     * Add a new task to the model.
     */
    void addTask(Task* t);

private:
    friend class TasksModelPrivate;
    TasksModelPrivate* const d;
};

#endif // TASKSMODEL_H
