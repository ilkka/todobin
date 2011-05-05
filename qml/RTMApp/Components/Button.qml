import QtQuick 1.0

Item {
    id: root
    width: 100
    height: 62

    // Margin for button background
    property int margin: 5

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

        MouseArea {
            id: hotspot
            anchors.fill: parent
        }
    }
}
