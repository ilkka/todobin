import QtQuick 1.1

Widget {
    id: root

    property string inputMask: field.inputMask
    property bool acceptableInput: field.acceptableInput
    property color textColor: field.color
    property string text: field.text
    property enumeration echoMode: field.echoMode
    property string hint: hintview.text

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
