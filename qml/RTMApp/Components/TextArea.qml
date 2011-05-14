import QtQuick 1.0

Widget {
    id: root
    width: 100
    height: 62

    property alias text: edit.text
    property alias hint: hintview.text

    property int fontPointSize: 16

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
        visible: hintview.text && !edit.activeFocus && !edit.text
    }

    TextEdit {
        id: edit
        anchors.fill: parent
        anchors.margins: root.margin * 2
        font.pointSize: root.fontPointSize
    }
}
