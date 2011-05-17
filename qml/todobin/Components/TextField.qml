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

    property int fontPointSize: 16

    clip: true

    width: Math.max(field.model.paintedWidth + 4 * margin, minimumWidth)
    height: field.model.paintedHeight + 4 * margin

    InputWidgetBackground {
        anchors.fill: parent
        anchors.margins: root.margin
    }

    Text {
        id: hintview
        anchors.fill: parent
        anchors.margins: root.margin * 2
        color: "#808080"
        font.pointSize: root.fontPointSize
        visible: hintview.text && !field.activeFocus && !field.text
    }

    TextInput {
        id: field
        anchors.fill: parent
        anchors.margins: root.margin * 2
        font.pointSize: root.fontPointSize
        autoScroll: false

        // This trick from Qt Components
        property variant model: Text { text: field.text; font.pointSize: root.fontPointSize; opacity: 0 }
    }
}
