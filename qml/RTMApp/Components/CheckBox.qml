import QtQuick 1.0

Widget {
    id: root

    property bool checked : false
    property string label : ""

    // If true, clicking the checkbox won't change its checked state
    // immediately, changing it is instead left to the user.
    property bool updateManually : false

    width: Math.max(background.width, labelview.width) + 2 * margin
    height: background.height + labelview.height + 2 * margin

    Rectangle {
        id: background
        border.color: "#555555"
        border.width: 2
        radius: 8
        color: "white"

        width: tick.width
        height: tick.width

        x: root.margin
        y: root.margin

        anchors.horizontalCenter: parent.horizontalCenter

        Image {
            id: tick
            visible: root.checked
            source: "../images/green_tick.svg"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: root.checked = !root.checked
        }
    }

    Text {
        id: labelview
        text: root.label
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: background.bottom
        anchors.margins: root.margin
    }
}
