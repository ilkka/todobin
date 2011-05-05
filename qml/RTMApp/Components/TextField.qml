import QtQuick 1.1

Widget {
    id: root

    property alias inputMask: field.inputMask
    property alias acceptableInput: field.acceptableInput
    property alias textColor: field.color
    property alias text: field.text
    property alias echoMode: field.echoMode
    property alias hint: hintview.text

    property int innerMargin: 5

    width: 100
    height: 30

    TextInput {
        id: field

        anchors.fill: parent
        anchors.margins: root.innerMargin

        onFocusChanged: {
            if (!field.focus && field.text.length == 0) {
                hintview.visible = true
            }
        }
    }

    Text {
        id: hintview
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent
            onClicked: {
                hintview.visible = false
                field.focus = true
            }
        }
    }
}
