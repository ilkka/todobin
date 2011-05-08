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
    Flickable {
        id: flickable
        anchors.top: instructions.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: okbutton.top
        contentHeight: Math.max(height, webview.height)
        contentWidth: Math.max(width, webview.width)
        WebView {
            id: webview
            url: api.authUrl
            preferredHeight: flickable.height
            preferredWidth: flickable.width
        }
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

    Rectangle {
        id: pleasewait
        anchors.fill: parent
        color: "black"
        opacity: 0.7
        Text {
            color: "white"
            anchors.centerIn: parent
            visible: false
            text: "Please wait..."
        }
    }
}

