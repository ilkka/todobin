#ifndef RTMINTERFACE_P_H
#define RTMINTERFACE_P_H

#include <QNetworkAccessManager>
#include <QSemaphore>
#include <QUrl>

/**
 * A struct for storing a pending task modification until it can be
 * performed.
 */
struct TaskModification
{
    QString listId;
    QString seriesId;
    QString taskId;

    enum ModificationType {
        MOD_NONE, MOD_CREATE, MOD_TITLE, MOD_ADD_TAG,
        MOD_REMOVE_TAG, MOD_ADD_NOTE,
        MOD_REMOVE_NOTE, MOD_COMPLETE,
        MOD_UNCOMPLETE
    };

    ModificationType type;

    // If type == MOD_ADD_TAG, this contains the tag to add.
    // If type == MOD_REMOVE_TAG, this contains the tag to remove.
    QString tag;

    // As for tag above
    QString note;
};

class RTMInterfacePrivate
{
public:
    QNetworkAccessManager* net;
    QSemaphore netSemaphore;

    QString frob;
    QUrl authUrl;
    QString token;
    QString username;
    QString fullname;
    QString timeline;

    /**
     * The pending task modification
     */
    TaskModification* pendingModification;
};

#endif // RTMINTERFACE_P_H
