#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QUrl>

#include "qmlapplicationviewer.h"
#include "settings.h"
#include "tasksmodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Settings settings;
    // Hardcode endpoint URL here
    settings.setValue("foursquare/endpoint", QUrl("http://api.rememberthemilk.com/services/rest/"));

    TasksModel model;

    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("settings", &settings);
    viewer.rootContext()->setContextProperty("tasksModel", &model);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/RTMApp/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
