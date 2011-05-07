#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QUrl>
#include <QFile>

#include "qmlapplicationviewer.h"
#include "settings.h"
#include "tasksmodel.h"
#include "xmltaskfactory.h"
#include "rtminterface.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Settings settings;

    TasksModel model;

    // Open dummydata file
    QFile f("qml/RTMApp/dummydata/all_tasks_response.xml");
    if (!f.open(QIODevice::ReadOnly)) {
        throw "Can't open XML file";
    }
    XmlTaskFactory factory;
    QObject::connect(&factory, SIGNAL(newTask(Task*)), &model, SLOT(addTask(Task*)));
    factory.setSource(&f);

    RTMInterface api;

    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("settings", &settings);
    viewer.rootContext()->setContextProperty("tasksModel", &model);
    viewer.rootContext()->setContextProperty("api", &api);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/RTMApp/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
