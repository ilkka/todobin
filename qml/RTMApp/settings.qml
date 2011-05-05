import QtQuick 1.0
import "./Components"

Rectangle {
    id: root
    width: 360
    height: 360

    Column {
        anchors.fill: parent

        TextField {
            hint: "API key"
        }
    }
}
