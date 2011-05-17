import QtQuick 1.0

Widget {
    id: root

    // Margin between background edge and label
    property int labelMargin: 15

    // Button label
    property string label: "Button"

    // Basic signals
    signal pressed
    signal clicked
    signal released

    // Size based on children's size
    width: childrenRect.width + margin * 2
    height: childrenRect.height + margin * 2

    Rectangle {
        id: background
        border.color: "#555555"
        border.width: 2
        radius: 8

        color: "#eeeeee"

        // Size based on label size
        width: label.paintedWidth + labelMargin * 2
        height: label.paintedHeight + labelMargin * 2

        anchors.centerIn: parent

        states: [
            State {
                name: "down"
                when: hotspot.pressed
                PropertyChanges {
                    target: background
                    color: "#afafaf"
                }
            }
        ]

        Text {
            id: label
            anchors.centerIn: parent
            text: root.label
        }

        MouseArea {
            id: hotspot
            anchors.fill: parent

            enabled: root.enabled

            onClicked: root.clicked()
            onPressed: root.pressed()
            onReleased: root.released()
        }
    }

    Rectangle {
        id: grey
        visible: !root.enabled
        anchors.centerIn: background
        width: background.width
        height: background.height
        radius: 8
        opacity: 0.8
        color: "#bbbbbb"
    }
}
