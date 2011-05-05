import QtQuick 1.0
import "./Components"

Rectangle {
    id: root
    width: 360
    height: 360

    Loader {
        id: mainviewloader
        anchors.fill: parent
        visible: status == Loader.Ready
    }

    Column {
        anchors.fill: parent
        visible: mainviewloader.status != Loader.Ready

        TextField {
            anchors.left: parent.left
            anchors.right: parent.right
            hint: "API key"
            text: settings.apikey
        }

        TextField {
            anchors.left: parent.left
            anchors.right: parent.right
            hint: "Secret"
            text: settings.secret
        }

        TextField {
            anchors.left: parent.left
            anchors.right: parent.right
            hint: "Endpoint"
            text: settings.endpoint
        }

        Button {
            label: "Save"
            onClicked: {
                mainviewloader.source = "main.qml"
            }
        }

        Button {
            label: "Exit"
            onClicked: Qt.quit();
        }
    }
}
