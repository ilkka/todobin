import QtQuick 1.0
import "./Components"
import "qmlprivate.js" as P
import "app.js" as App

Column {
    id: root
    anchors.fill: parent

    signal requestSettingsView

    Button {
        label: "Quit"
        onClicked: Qt.quit()
    }

    Button {
        label: "Settings"
        onClicked: root.requestSettingsView()
    }
}
