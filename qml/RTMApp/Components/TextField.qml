import QtQuick 1.0

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

    Rectangle {
        gradient: Gradient {
            GradientStop {
                position: 0.00;
                color: "#dedede";
            }
            GradientStop {
                position: 1.00;
                color: "#f0f0f0";
            }
        }

        border.color: "#555555"
        border.width: 1
        radius: 5

        anchors.fill: parent
        anchors.margins: root.innerMargin

        TextInput {
            id: field
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: root.innerMargin

            onFocusChanged: {
                if (!field.focus && field.text.length == 0) {
                    hintview.visible = true
                }
            }
        }

        Text {
            id: hintview
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.margins: root.innerMargin
            color: "#808080"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    hintview.visible = false
                    field.focus = true
                }
            }
        }
    }
}
