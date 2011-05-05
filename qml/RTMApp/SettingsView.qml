import QtQuick 1.0
import "./Components"

Rectangle {
    id: root
    width: 360
    height: 360

    signal settingsDone

    Column {
        anchors.fill: parent

        TextField {
            id: apikeyfield
            anchors.left: parent.left
            anchors.right: parent.right
            hint: "API key"
            text: settings.apikey
        }

        TextField {
            id: secretfield
            anchors.left: parent.left
            anchors.right: parent.right
            hint: "Secret"
            text: settings.secret
        }

        TextField {
            id: endpointfield
            anchors.left: parent.left
            anchors.right: parent.right
            hint: "Endpoint"
            text: settings.endpoint
        }

        Button {
            label: "Save"
            onClicked: {
                settings.apikey = apikeyfield.text
                settings.secret = secretfield.text
                settings.endpoint = endpointfield.text
                root.settingsDone()
            }
        }

        Button {
            label: "Exit"
            onClicked: Qt.quit();
        }
    }
}
