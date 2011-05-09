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
                anchors.margins: internalMargin
                radius: 8
                color: "#e0e0e0";
            }

            // Tapping the delegate puts it in details mode
            MouseArea {
                anchors.fill: parent
                onClicked: task.state = "details"
            }

            Item {
                id: toplayout
                x: internalMargin
                width: tasklist.width - 2 * internalMargin
                height: tasktitle.paintedHeight
                        + tasktags.paintedHeight
                        + taskduedate.paintedHeight
                        + 4 * internalMargin
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

            Item {
                id: detailslayout
                x: internalMargin
                width: tasklist.width - 2 * internalMargin
                anchors { top: toplayout.bottom; bottom: parent.bottom }
                opacity: task.detailsOpacity

                Text {
                    anchors.centerIn: parent
                    text: "This is details"
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
                // Scroll the list to place the task at the top
                PropertyChanges {
                    target: task.ListView.view
                    explicit: true
                    contentY: task.y
                }
            }

            transitions: Transition {
                NumberAnimation {
                    duration: 300
                    properties: "detailsOpacity,height,contentY"
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
