import QtQuick 1.0
import "./Components"

Rectangle {
    id: root
    width: 200
    height: 200

    signal requestSettingsView

    ListView {
        anchors.top: parent.top
        anchors.bottom: controls.top
        anchors.left: parent.left
        anchors.right: parent.right

        clip: true

        model: tasksModel
        delegate: Text {
            text: title
                  + (tags.length > 0 ? " [" + tags + "]" : "")
                  + (due.length > 0 ? " (due " + due + ")" : "")
        }

        Component.onCompleted: tasksModel.populate()
    }

    Row {
        id: controls
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
