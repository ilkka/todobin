import QtQuick 1.0

Flipable {
    id: flipper
    width: 400
    height: 400

    transform: Rotation {
        id: rotation
        origin.x: flipper.width / 2
        origin.y: flipper.height / 2
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
        anchors.fill: parent
        onRequestSettingsView: flipper.state = "back"
    }

    back: SettingsView {
        anchors.fill: parent
        onSettingsDone: flipper.state = "front"
    }
}
