import QtQuick 1.0

Item {
    id: root

    // Margin between component edge and background
    property int margin: 5

    // Margin between background edge and label
    property int labelMargin: 5

    // Button label
    property string label: "Button"

    // Basic signals
    signal pressed
    signal clicked
    signal released

    Rectangle {
        id: background
        border.color: "#555555"
        border.width: 2
        radius: 8

        gradient: Gradient {
            GradientStop {
                id: lightside
                position: 0.00;
                color: "#eeeeee";
            }
            GradientStop {
                id: darkside
                position: 1.00;
                color: "#afafaf";
            }
        }

        anchors.fill: parent
        anchors.margins: root.margin

        Text {
            id: label
            anchors.centerIn: parent
            text: root.label
        }

        MouseArea {
            id: hotspot
            anchors.fill: parent

            onClicked: root.clicked()
            onPressed: root.pressed()
            onReleased: root.released()
        }
    }
}
