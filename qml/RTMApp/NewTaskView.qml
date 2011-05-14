import QtQuick 1.0
import "./Components"

Item {
    id: root
    width: 480
    height: 800

    signal requestCreateTask(string title, string tags, string estimate, string note)

    Column {
        id: col1
        anchors { top: parent.top; bottom: parent.bottom; left: parent.left; right: col2.left }

        TextField {
            anchors.left: parent.left
            width: parent.width
            hint: "Task title"
        }

        TextField {
            anchors.left: parent.left
            width: parent.width
            hint: "Tags"
        }

        TextField {
            anchors.left: parent.left
            width: parent.width
            hint: "Estimate"
        }

        TextArea {
            id: notefield
            anchors.left: parent.left
            width: parent.width
            hint: "Note"
        }
        Row {
            id: controls
            width: parent.width
            Button {
                id: save
                label: "Create"
                onClicked: root.requestCreateTask(titlefield.text,
                                                  tagsfield.text,
                                                  estimatefield.text,
                                                  notefield.text)
            }
        }
    }

    onRequestCreateTask: {
        console.debug("Would create task: " + title + " "
                      + tags + " " + estimate + " " + note)
    }

    Column {
        id: col2
        anchors { top: parent.top; right: parent.right; bottom: parent.bottom }
        width : 0
    }

    states: State {
        name: "landscape"
        when: root.width > 700 && root.width > 1.5 * root.height
        PropertyChanges {
            target: col2
            width: root.width / 2
        }
        PropertyChanges {
            target: notefield
            parent: col2
        }
    }
}

