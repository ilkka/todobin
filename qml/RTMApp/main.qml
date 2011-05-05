import QtQuick 1.0

Flipable {
    id: root
    width: 360
    height: 360

    front: TaskView {}
    back: SettingsView {}
}
