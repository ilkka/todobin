import QtQuick 1.0

Widget {
    id: root
    width: 80
    height: 200

    property int value: list.currentIndex + minimumValue
    property int minimumValue: 0
    property int maximumValue: 10

    property int fontPointSize: 20

    ListModel {
        id: spinnermodel
    }

    function adjustItems() {
        var newCount = maximumValue - minimumValue + 1
        while (spinnermodel.count > newCount) {
            spinnermodel.remove(spinnermodel.count - 1)
            list.contentHeight -= list.textmodel.height + root.margin
        }
        while (spinnermodel.count < newCount) {
            spinnermodel.append({})
            list.contentHeight += list.textmodel.height + root.margin
        }
        if (value < minimumValue) {
            value = minimumValue
        }
        if (value > maximumValue) {
            value = maximumValue
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

        ListView {
            id: list
            anchors.fill: parent
            anchors.margins: window.radius / 2
            model: spinnermodel
            clip: true

            property variant textmodel: Text { font.pointSize: root.fontPointSize; text: "1" }
            property int endpadding: list.height / 2 - textmodel.paintedHeight / 2

            preferredHighlightBegin: endpadding
            preferredHighlightEnd: endpadding + textmodel.height
            highlightRangeMode: moving ? ListView.NoHighlightRange : ListView.StrictlyEnforceRange
            highlightFollowsCurrentItem: true

            header: Item {
                width: list.width
                height: list.endpadding
            }

            footer: Item {
                width: list.width
                height: list.endpadding
            }

            spacing: root.margin

            delegate: Text {
                font.pointSize: root.fontPointSize
                width: list.width
                horizontalAlignment: Text.AlignHCenter
                text: root.minimumValue + index
            }

            onContentYChanged: {
                // calculate new value for currentIndex
                console.debug("ContentY: " + contentY)
                var yOffset = textmodel.paintedHeight + root.margin
                var newIndex = Math.floor(contentY / yOffset)
                if (newIndex < 0) { newIndex = 0 }
                else if (newIndex >= count) { newIndex = count - 1 }
                console.debug("New value be " + newIndex)
                currentIndex = newIndex
            }

            Component {
                id: highlight
                Rectangle {
                    width: parent.width
                    height: list.textmodel.paintedHeight + 2 * root.margin
                    color: "#5566ee"
                    opacity: 0.7
                }
            }

            onHighlightRangeModeChanged: {
                console.debug("Highlight range mode now " + highlightRangeMode)
            }

            onCurrentItemChanged: console.debug("Current item changed")

            highlight: highlight
        }
    }

    onValueChanged: console.log("Value now " + value)

    Component.onCompleted: {
        adjustItems()
        list.currentIndex = 0
    }
}
