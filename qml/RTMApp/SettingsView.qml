import QtQuick 1.0
import QtWebKit 1.0
import "./Components"

Rectangle {
    id: root
    width: 360
    height: 360

    signal settingsDone

    Flickable {
        Column {
            anchors.top: parent.top
            width: root.width

            TextField {
                id: apikeyfield
                anchors.left: parent.left
                anchors.right: parent.right
                hint: "API key"
            }

            TextField {
                id: secretfield
                anchors.left: parent.left
                anchors.right: parent.right
                hint: "Secret"
            }

            TextField {
                id: endpointfield
                anchors.left: parent.left
                anchors.right: parent.right
                hint: "Endpoint"
            }

            Button {
                label: "Save"
                onClicked: {
                    settings.setValue("foursquare/apikey", apikeyfield.text)
                    settings.setValue("foursquare/secret", secretfield.text)
                    settings.setValue("foursquare/endpoint", endpointfield.text)
                }
            }

            Button {
                label: "Load auth page"
                onClicked: {
                    webview.url = api.getAuthUrl()
                }
            }

            WebView {
                id: webview
                anchors.left: parent.left
                anchors.right: parent.right
                height: 500
            }
        }
    }

    Component.onCompleted: {
        apikeyfield.text = settings.value("foursquare/apikey")
        secretfield.text = settings.value("foursquare/secret")
        endpointfield.text = settings.value("foursquare/endpoint")
    }
}
