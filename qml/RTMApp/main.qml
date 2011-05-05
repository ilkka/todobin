import QtQuick 1.0
import "./Components"

Rectangle {
    width: 360
    height: 360
    Button {
        anchors.centerIn: parent
        label: "Test if we're logged in"
        onClicked: {
            Qt.quit();
        }
    }
}
