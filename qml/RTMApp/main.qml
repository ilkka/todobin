import QtQuick 1.0

Rectangle {
    id: root
    width: 400
    height: 400

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

