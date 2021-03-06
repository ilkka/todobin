import QtQuick 1.0
import "./Components"

Item {
    id: root
    width: 480
    height: 800

    signal completed

    Column {
        id: col1
        anchors { top: parent.top; bottom: parent.bottom; left: parent.left; right: col2.left }

        TextField {
            id: titlefield
            width: parent.width
            hint: "Task title"
        }

        TextField {
            id: tagsfield
            width: parent.width
            hint: "Tags"
        }

        TextField {
            id: estimatefield
            width: parent.width
            hint: "Estimate"
        }

        TextArea {
            id: notefield
            width: parent.width
            height: parent.height / 3
            hint: "Note"
        }

        Row {
            id: controls
            width: parent.width
            Button {
                id: save
                label: "Create"
                enabled: titlefield.text
                onClicked: {
                    api.requestCreateTask(titlefield.text)
                    titlefield.text = ""
                    tagsfield.text = ""
                    notefield.text = ""
                    root.completed()
                    // TODO: do something with the rest of the fields
                }
            }
        }
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

