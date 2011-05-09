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
                    anchors.right: taskControls.left
                    anchors.margins: task.internalMargin
                    readOnly: true
                    wrapMode: TextEdit.Wrap
                }
                TextEdit {
                    id: tasktags
                    text: (tags.length > 0 ? "Tags: " + tags : "")
                    anchors.top: tasktitle.bottom
                    anchors.left: parent.left
                    anchors.right: taskControls.left
                    anchors.margins: task.internalMargin
                    readOnly: true
                    wrapMode: TextEdit.Wrap
                }
                TextEdit {
                    id: taskduedate
                    text: (due.length > 0 ? "Due " + due : "")
                    anchors.top: tasktags.bottom
                    anchors.left: parent.left
                    anchors.right: taskControls.left
                    anchors.margins: task.internalMargin
                    readOnly: true
                    wrapMode: TextEdit.Wrap
                }
                Column {
                    id: taskControls
                    anchors { top: parent.top; right: parent.right; margins: task.internalMargin }
                    width: task.state == "details" || isCompleted ? childrenRect.width : 0
                    height: task.state == "details" || isCompleted ? childrenRect.height : 0
                    Item {
                        id: completedMarker
                        width: isCompleted ? Math.max(tickImage.width, completedLabel.width) : 0
                        height: isCompleted ? tickImage.height + completedLabel.height : 0
                        visible: isCompleted
                        Image {
                            id: tickImage
                            anchors { top: parent.top; horizontalCenter: parent.horizontalCenter }
                            source: "images/green_tick.svg"
                        }
                        Text {
                            id: completedLabel
                            text: "Completed"
                            anchors { top: tickImage.bottom; horizontalCenter: tickImage.horizontalCenter }
                        }
                    }

                    // Close button that is only visible in expanded mode
                    Button {
                        id: closebutton
                        label: "Close"
                        opacity: task.detailsOpacity
                        onClicked: task.state = ""
                    }
                }
            }

            // Tapping the delegate puts it in details mode
            MouseArea {
                anchors.fill: parent
                visible: task.state != "details"
                onClicked: {
                    tasklist.positionViewAtIndex(index, ListView.Beginning)
                    task.state = "details"
                }
            }

            Item {
                id: detailslayout
                x: task.internalMargin * 2
                width: tasklist.width - 4 * task.internalMargin
                height: notelist.height + 2 * task.internalMargin
                anchors { top: toplayout.bottom }

                opacity: task.detailsOpacity

                Column {
                    id: notelist
                    anchors { left: detailslayout.left; right: detailslayout.right }
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
                    height: toplayout.height + detailslayout.height + 2 * task.internalMargin
                }
            }

            Behavior on detailsOpacity { NumberAnimation { duration: 300 } }
            Behavior on height { NumberAnimation { duration: 300 } }
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
