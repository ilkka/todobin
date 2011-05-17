import QtQuick 1.0

Widget {
    id: root
    width: 80
    height: 200

    property int value: 0
    property int minimumValue: 0
    property int maximumValue: 0

    property int fontPointSize: 20

    ListModel {
        id: spinnermodel
        ListElement {}
    }

    function adjustItems() {
        var newCount = maximumValue - minimumValue - 1
        while (spinnermodel.count > newCount) {
            spinnermodel.remove(spinnermodel.count - 1)
        }
        while (spinnermodel.count < newCount) {
            spinnermodel.append({})
        }
    }

    onMinimumValueChanged: adjustItems()
    onMaximumValueChanged: adjustItems()

    Rectangle {
        id: window
        border.width: 2
        border.color: "black"
        radius: 8
        anchors.fill: parent
        anchors.margins: root.margin
        clip: true

        ListView {
            id: flicker
            anchors.fill: parent
            model: spinnermodel

            property variant textmodel: Text { font.pointSize: root.fontPointSize; text: "1" }
            property int endpadding: flicker.height / 2 - textmodel.paintedHeight / 2 - root.margin

            header: Item {
                width: flicker.width
                height: flicker.endpadding
            }

            footer: Item {
                width: flicker.width
                height: flicker.endpadding
            }

            spacing: root.margin

            delegate: Text {
                font.pointSize: root.fontPointSize
                width: flicker.width
                horizontalAlignment: Text.AlignHCenter
                text: root.minimumValue + index
            }

            // This handler makes the flickable snap to the numbers
            onMovementEnded: {
                var yOffset = textmodel.paintedHeight + root.margin
                var overshoot = contentY % yOffset
                if (overshoot >= yOffset / 2) {
                    contentY += yOffset - overshoot
                } else {
                    contentY -= overshoot
                }
                value = Math.floor(contentY / yOffset) + 1
            }
        }

        Rectangle {
            id: highlight
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            height: flicker.textmodel.paintedHeight + 2 * root.margin
            color: "#5566ee"
            opacity: 0.7
        }
    }
}