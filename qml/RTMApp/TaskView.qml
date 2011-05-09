import QtQuick 1.0
import "./Components"

Rectangle {
    id: root
    width: 200
    height: 200

    signal requestSettingsView

    Component {
        id: taskDelegate
        Item {
            width: tasklist.width
            height: tasktitle.paintedHeight
                    + tasktags.paintedHeight
                    + taskduedate.paintedHeight
                    + 6 * 5
            Rectangle {
                anchors.fill: parent
                anchors.margins: 5
                radius: 8
                color: "#e0e0e0";
                Text {
                    id: tasktitle
                    text: "<b>" + title + "</b>"
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: 5
                }
                Text {
                    id: tasktags
                    text: (tags.length > 0 ? " [" + tags + "]" : "")
                    anchors.top: tasktitle.bottom
                    anchors.left: parent.left
                    anchors.margins: 5
                }
                Text {
                    id: taskduedate
                    text: (due.length > 0 ? " (due " + due + ")" : "")
                    anchors.top: tasktags.bottom
                    anchors.left: parent.left
                    anchors.margins: 5
                }
            }
        }
    }

    ListView {
        id: tasklist

        anchors.top: parent.top
        anchors.bottom: controls.top
        anchors.left: parent.left
        anchors.right: parent.right

        clip: true

        model: tasksModel
        delegate: taskDelegate

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
