import QtQuick 1.0
import "./Components"
import "qmlprivate.js" as P
import "app.js" as Applib

Column {
    id: root
    anchors.fill: parent

    Button {
        label: "Test if we're logged in"
        onClicked: {
            P.priv(root).app.test_login();
        }
    }

    Button {
        label: "Quit"
        onClicked: Qt.quit()
    }

    Component.onCompleted: P.priv(root).app = Applib.init(settings)
}
