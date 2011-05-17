#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QUrl>
#include <QFile>

#include "qmlapplicationviewer.h"
#include "settings.h"
#include "tasksmodel.h"
#include "xmltaskfactory.h"
#include "rtminterface.h"

#ifdef STATIC_DATA_TEST
#include "dummyapi.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Settings settings;

    TasksModel model;

    XmlTaskFactory factory;
    QObject::connect(&factory, SIGNAL(newTask(Task*)), &model, SLOT(addTask(Task*)));

    QmlApplicationViewer viewer;

#ifndef STATIC_DATA_TEST
    RTMInterface api;
#else
    DummyApi api;
#endif

    // connect api, model and factory to enable task list fetching
    // and adding the tasks to the model
    api.connect(&model, SIGNAL(requestTaskList()), SLOT(requestTaskList()));
    factory.connect(&api, SIGNAL(taskListReceived(QIODevice*)), SLOT(parseTaskList(QIODevice*)));
    // Provide API to QML UI
    viewer.rootContext()->setContextProperty("api", &api);

    viewer.rootContext()->setContextProperty("settings", &settings);
    viewer.rootContext()->setContextProperty("tasksModel", &model);

    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);

#ifndef ON_MAEMO_5
    // For testing/debug
    viewer.setResizeMode(QmlApplicationViewer::SizeViewToRootObject);
#endif

    viewer.setMainQmlFile(QLatin1String("qml/RTMApp/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
