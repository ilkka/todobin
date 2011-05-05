import QtQuick 1.0

Widget {
    id: root

    property alias text: field.text

    property alias inputMask: field.inputMask
    property alias acceptableInput: field.acceptableInput
    property alias textColor: field.color
    property alias echoMode: field.echoMode
    property alias hint: hintview.text

    property int minimumWidth: 100

    clip: true

    width: Math.max(field.model.paintedWidth + 10, minimumWidth)
    height: field.model.paintedHeight + 10

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
        radius: 8

        anchors.fill: parent
    }

    Text {
        id: hintview
        anchors.fill: parent
        anchors.margins: 5
        color: "#808080"
        visible: hintview.text && !field.activeFocus && !field.text
    }

    TextInput {
        id: field
        anchors.fill: parent
        anchors.margins: 5

        autoScroll: false

        // This trick from Qt Components
        property variant model: Text { text: field.text; visible: false }

        onFocusChanged: {
            if (!field.focus && field.text.length == 0) {
                hintview.visible = true
            }
        }
    }
}
