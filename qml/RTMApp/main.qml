import QtQuick 1.0

Rectangle {
    id: root
    width: 480
    height: 800

    states: State {
        name: "landscape"
        PropertyChanges {
            target: root
            width: 800
            height: 480
        }
    }

    Loader {
        id: pageloader
        anchors.fill: parent
        source: "Splash.qml"
    }

    Connections {
        target: api
        onAuthenticationNeeded: pageloader.source = "AuthView.qml"
        onInitializationCompleted: pageloader.source = "TaskView.qml"
    }

    Component.onCompleted: {
        api.initialize();
    }
}

