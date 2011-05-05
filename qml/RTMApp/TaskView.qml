import QtQuick 1.0
import "./Components"
import "qmlprivate.js" as P
import "app.js" as Applib

Column {
    id: root
    anchors.fill: parent

    signal requestSettingsView

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

    Button {
        label: "Settings"
        onClicked: root.requestSettingsView()
    }

    Component.onCompleted: {
        P.priv(root).app = Applib.init(settings)
        if (settings.apikey.length === 0 || settings.secret.length === 0) {
            root.requestSettingsView()
        }
    }
}
