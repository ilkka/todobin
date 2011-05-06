#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QUrl>
#include <QFile>

#include "qmlapplicationviewer.h"
#include "settings.h"
#include "tasksmodel.h"
#include "xmltaskfactory.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Settings settings;
    // Hardcode endpoint URL here
    settings.setValue("foursquare/endpoint", QUrl("http://api.rememberthemilk.com/services/rest/"));

    TasksModel model;

    // Open dummydata file
    QFile f("qml/RTMApp/dummydata/all_tasks_response.xml");
    if (!f.open(QIODevice::ReadOnly)) {
        throw "Can't open XML file";
    }
    XmlTaskFactory factory;
    QObject::connect(&factory, SIGNAL(newTask(Task*)), &model, SLOT(addTask(Task*)));
    factory.setSource(&f);

    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("settings", &settings);
    viewer.rootContext()->setContextProperty("tasksModel", &model);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/RTMApp/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
