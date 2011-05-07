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

    function showAuthView() {
        pageloader.source = "AuthView.qml"
    }

    Connections {
        target: api
        onAuthenticationNeeded: showAuthView()
    }

    Component.onCompleted: {
        api.initialize();
    }
}

