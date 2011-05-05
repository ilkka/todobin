#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QUrl>

#include "qmlapplicationviewer.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Settings settings;

    // Hardcode endpoint URL here
    settings.setEndpoint(QUrl("http://api.rememberthemilk.com/services/rest/"));

    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("settings", &settings);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/RTMApp/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
