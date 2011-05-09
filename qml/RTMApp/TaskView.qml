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
            id: task
            // margin controlling amount of space between items inside
            // the delegate
            property int internalMargin: 5

            // Common opacity for all the details
            property real detailsOpacity: 0

            width: tasklist.width
            height: toplayout.height + 2 * internalMargin

            Rectangle {
                id: background
                anchors.fill: parent
                anchors.margins: task.internalMargin
                radius: 8
                color: "#e0e0e0";
            }

            Item {
                id: toplayout
                x: 2 * internalMargin
                width: tasklist.width - 4 * task.internalMargin
                height: tasktitle.paintedHeight
                        + tasktags.paintedHeight
                        + taskduedate.paintedHeight
                        + 4 * task.internalMargin
                TextEdit {
                    id: tasktitle
                    text: "<b>" + title + "</b>"
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: task.internalMargin
                    readOnly: true
                    wrapMode: TextEdit.Wrap
                }
                TextEdit {
                    id: tasktags
                    text: (tags.length > 0 ? "Tags: " + tags : "")
                    anchors.top: tasktitle.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: task.internalMargin
                    readOnly: true
                    wrapMode: TextEdit.Wrap
                }
                TextEdit {
                    id: taskduedate
                    text: (due.length > 0 ? "Due " + due : "")
                    anchors.top: tasktags.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: task.internalMargin
                    readOnly: true
                    wrapMode: TextEdit.Wrap
                }
                // Close button that is only visible in expanded mode
                Button {
                    id: closebutton
                    label: "Close"
                    anchors.top: parent.top
                    anchors.right: parent.right
                    anchors.margins: task.internalMargin
                    opacity: task.detailsOpacity
                    onClicked: task.state = ""
                }
            }

            // Tapping the delegate puts it in details mode
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    tasklist.positionViewAtIndex(index, ListView.Beginning)
                    task.state = "details"
                }
            }

            Item {
                id: detailslayout
                x: task.internalMargin
                width: tasklist.width - 2 * task.internalMargin

                anchors { top: toplayout.bottom; bottom: parent.bottom }
                opacity: task.detailsOpacity

                Column {
                    id: notelist
                    anchors.fill: detailslayout
                    anchors.margins: task.internalMargin
                    spacing: task.internalMargin

                    Text {
                        text: "<b>Notes:</b>"
                    }

                    Repeater {
                        model: notes
                        TextEdit {
                            width: notelist.width
                            readOnly: true
                            wrapMode: TextEdit.Wrap
                            text: modelData
                        }
                    }
                }
            }

            states: State {
                name: "details"
                // Show the details and scale the task to take up the
                // whole view
                PropertyChanges {
                    target: task
                    detailsOpacity: 1
                    height: tasklist.height
                }
                // Format the delegates so the close button isn't covered
                PropertyChanges { target: tasktitle; anchors.right: closebutton.left; }
                PropertyChanges { target: tasktags; anchors.right: closebutton.left; }
                PropertyChanges { target: taskduedate; anchors.right: closebutton.left; }
            }

            transitions: Transition {
                NumberAnimation {
                    duration: 300
                    properties: "detailsOpacity,height"
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
