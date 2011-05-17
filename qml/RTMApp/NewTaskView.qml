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

        DatePicker {
            id: datepicker
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
