import QtQuick 1.0
import QtWebKit 1.0
import "./Components"

Rectangle {
    id: root
    width: 400
    height: 400
    color: "black"

    Text {
        id: instructions
        text: "Authenticate using the browser, press OK when done."
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        color: "white"
    }
    WebView {
        id: webview
        anchors.top: instructions.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: okbutton.top
        url: api.authUrl
    }
    Button {
        id: okbutton
        label: "OK"
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            pleasewait.visible = true
            api.authenticationCompleted()
        }
    }

    Text {
        id: pleasewait
        visible: false
        anchors.fill: parent
        text: "Please wait..."
    }
}

