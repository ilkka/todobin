import QtQuick 1.1

Item {
    id: widgetroot

    // Margin between component edge and background
    property int margin: 5

    // Size based on children's size
    width: childrenRect.width + margin * 2
    height: childrenRect.height + margin * 2
}
