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
                y: 2 * internalMargin
                width: tasklist.width - 4 * task.internalMargin
                height: Math.max(childrenRect.height,
                                 controlsBox.height + 2 * task.internalMargin)
                clip: true

                Behavior on height {
                    NumberAnimation { duration: 300 }
                }

                // This item wraps the info that is always visible
                Column {
                    id: taskinfo
                    anchors.top: parent.top
                    width: parent.width - controlsBox.width - 2 * task.internalMargin
                    height: childrenRect.height

                    TextEdit {
                        id: tasktitle
                        width: parent.width
                        text: "<b>" + title + "</b>"
                        readOnly: true
                        wrapMode: TextEdit.Wrap
                    }
                    TextEdit {
                        id: tasktags
                        width: parent.width
                        text: (tags.length > 0 ? "Tags: " + tags : "")
                        readOnly: true
                        wrapMode: TextEdit.Wrap
                    }
                    TextEdit {
                        id: taskduedate
                        width: parent.width
                        text: (due.length > 0 ? "Due " + due : "")
                        readOnly: true
                        wrapMode: TextEdit.Wrap
                    }
                }

            }

            Item {
                id: controlsBox
                anchors.top: toplayout.top
                anchors.right: toplayout.right
                height: childrenRect.height
                width: Math.max(completedMarker.width, closebutton.width)

                // Checkbox both for showing the "done" state and for
                // marking tasks done
                CheckBox {
                    id: completedMarker
                    anchors { top: parent.top; right: parent.right; margins: task.internalMargin }
                    updateManually: true
                    checked: isCompleted
                    onCheckRequested: {
                        api.requestMarkTaskCompleted(listId, seriesId, taskId)
                    }
                    onUncheckRequested: {
                        api.requestMarkTaskUncompleted(listId, seriesId, taskId)
                    }
                }

                // Close button that is only visible in expanded mode
                Button {
                    id: closebutton
                    label: "Close"
                    anchors { top: parent.top; right: parent.right; margins: task.internalMargin }
                    onClicked: task.state = ""
                    visible: false
                    opacity: task.detailsOpacity
                    states: [
                        State {
                            when: task.state == "details"
                            PropertyChanges {
                                target: closebutton
                                anchors.top: completedMarker.bottom
                                visible: true
                            }
                        }
                    ]
                }
            }

            // Tapping the delegate puts it in details mode
            MouseArea {
                anchors.top: parent.top; anchors.bottom: parent.bottom
                anchors.left: parent.left; anchors.right: controlsBox.left
                visible: task.state != "details"
                onClicked: {
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

            // Move the view only after resizes have happened
            transitions: Transition {
                SequentialAnimation {
                    ParallelAnimation {
                        NumberAnimation { properties: "detailsOpacity,height"; duration: 300 }
                    }
                    ScriptAction { script: tasklist.positionViewAtIndex(index, ListView.Contain) }
                }
            }
        }
    }

    Flipable {
        id: flipper

        property bool flipped: false

        anchors.top: parent.top
        anchors.bottom: controls.top
        anchors.left: parent.left
        anchors.right: parent.right

        front: ListView {
            id: tasklist
            clip: true
            anchors.fill: parent

            model: tasksModel
            delegate: taskDelegate

            Component.onCompleted: tasksModel.populate()
        }

        back: Loader {
            id: flipbackloader
            anchors.fill: parent
        }

        transform: Rotation {
            id: fliprotation
            origin.x: flipper.width/2; origin.y: flipper.height/2
            axis.x: 0; axis.y: 1; axis.z: 0
            angle: 0
        }

        states: State {
            name: "back"
            when: flipper.flipped
            PropertyChanges {
                target: fliprotation; angle: 180
            }
        }

        transitions: Transition {
            NumberAnimation { target: fliprotation; property: "angle"; duration: 300 }
        }
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
            label: "New"
            onClicked: {
                flipbackloader.source = "NewTaskView.qml"
                flipper.flipped = true
            }
        }
    }

    Connections {
        target: flipbackloader.item
        onCompleted: flipper.flipped = false
    }
}
