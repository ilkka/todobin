import QtQuick 1.0
import "./Components"
import "qmlprivate.js" as P
import "app.js" as App

Column {
    id: root

    signal requestSettingsView

    Row {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Button {
            label: "Quit"
            onClicked: Qt.quit()
        }

        Button {
            label: "Settings"
            onClicked: root.requestSettingsView()
        }
    }
}
