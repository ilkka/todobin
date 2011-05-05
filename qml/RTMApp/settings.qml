import QtQuick 1.0
import "./Components"

Rectangle {
    id: root
    width: 360
    height: 360

    Column {
        anchors.fill: parent

        TextField {
            anchors.left: parent.left
            anchors.right: parent.right
            hint: "API key"
        }

        TextField {
            anchors.left: parent.left
            anchors.right: parent.right
            hint: "Secret"
        }

        TextField {
            anchors.left: parent.left
            anchors.right: parent.right
            hint: "Endpoint"
        }
    }
}
