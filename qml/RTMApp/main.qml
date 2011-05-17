import QtQuick 1.0
import "./Components"

Rectangle {
    id: root
    width: 800
    height: 480

    Loader {
        id: pageloader
        anchors.fill: parent
        source: "Splash.qml"
    }

    Connections {
        target: api
        onAuthenticationNeeded: pageloader.source = "AuthView.qml"
        onInitializationCompleted: pageloader.source = "TaskListView.qml"
    }

    Component.onCompleted: {
        api.initialize();
    }
}

