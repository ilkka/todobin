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

    Button {
        label: viewer.fullscreen ? "Restore" : "Fullscreen"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onClicked: {
            if (viewer.fullscreen) {
                viewer.showMaximized()
            } else {
                viewer.showFullScreen()
            }
        }
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

