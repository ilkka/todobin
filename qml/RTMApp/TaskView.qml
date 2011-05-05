import QtQuick 1.0
import "./Components"
import "qmlprivate.js" as P
import "app.js" as App

Column {
    id: root
    anchors.fill: parent

    signal requestSettingsView

    Button {
        label: "Test if we're logged in"
        onClicked: {
            App.test_login();
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
        if (settings.value("foursquare/apikey").length === 0 || settings.value("foursquare/secret").length === 0) {
            root.requestSettingsView()
        }
    }
}
