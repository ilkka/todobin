import QtQuick 1.0

Flipable {
    id: root
    width: 360
    height: 360

    transform: Rotation {
        id: rotation
        origin.x: root.width / 2
        origin.y: root.height / 2
        axis.x: 0
        axis.y: 1
        axis.z: 0
        angle: 0

        Behavior on angle {
            NumberAnimation { target: rotation; property: "angle"; duration: 200 }
        }
    }

    states: [
        State {
            name: "front"
        },
        State {
            name: "back"
            PropertyChanges {
                target: rotation
                angle: 180
            }
        }
    ]

    state: "front"

    front: TaskView {
        onRequestSettingsView: root.state = "back"
    }

    back: SettingsView {
    }
}
