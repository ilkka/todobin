import QtQuick 1.0
import "./Components"

Rectangle {
    id: root
    width: 480
    height: 800

    states: State {
        name: "landscape"
    }

    transitions: [
        Transition {
            ScriptAction {
                script: {
                    var tmpw = root.width
                    root.width = root.height
                    root.height = tmpw
                }
            }
        }
    ]

    Loader {
        id: pageloader
        anchors.fill: parent
        source: "Splash.qml"
    }

    Button {
        id: orientationbutton
        anchors { right: parent.right; bottom: parent.bottom }
        label: "Orient"
        onClicked: root.state = (root.state == "") ? "landscape" : ""
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

