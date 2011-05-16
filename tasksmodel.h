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
        TitleRole = Qt::UserRole + 1,
        DueRole,
        TagsRole,
        NotesRole,
        CompletedRole,
        IsCompletedRole,
        ListIdRole,
        SeriesIdRole,
        TaskIdRole
    };

    explicit TasksModel(QObject *parent = 0);
    virtual ~TasksModel();

    /**
     * Request to populate the model.
     */
    Q_INVOKABLE void populate();

    /** @see QAbstractListModel::rowCount
      */
    int rowCount(const QModelIndex &parent) const;

    /** @see QAbstractListModel::data
      */
    QVariant data(const QModelIndex &index, int role) const;

    /** @see QAbstractListModel::headerData
      */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    /**
     * Get index for task with given IDs.
     * @return index for task or an invalid ID if no such task exists
     * in model.
     */
    QModelIndex indexForTask(const QString& listId,
                             const QString& seriesId,
                             const QString& taskId);

    /**
     * Check if model has task for given IDs.
     */
    Q_INVOKABLE bool hasTask(const QString& listId,
                             const QString& seriesId,
                             const QString& taskId);

signals:
    /**
     * Emitted when the model wants a task list. The handling slot
     * should call addTask to add the tasks.
     */
    void requestTaskList();

public slots:
    /**
     * Add a new task to the model.
     */
    void addTask(Task* t);

    /**
     * Change the completed state of the task at the given row.
     */
    void setTaskCompleted(int index, bool completed);

private:
    friend class TasksModelPrivate;
    TasksModelPrivate* const d;
};

#endif // TASKSMODEL_H
