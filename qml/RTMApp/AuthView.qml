import QtQuick 1.0
import QtWebKit 1.0
import "./Components"

Rectangle {
    id: root
    width: 400
    height: 400

    Rectangle {
        id: instructions
        color: "black"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: instructiontext.paintedHeight
        Text {
            id: instructiontext
            text: "Authenticate using the browser, press OK when done."
            anchors.centerIn: parent
            color: "white"
        }
    }

    Flickable {
        id: flickable
        anchors.top: instructions.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: buttons.top
        contentHeight: Math.max(height, webview.height)
        contentWidth: Math.max(width, webview.width)
        clip: true
        WebView {
            id: webview
            url: api.authUrl
            preferredHeight: flickable.height
            preferredWidth: flickable.width
            settings.javascriptEnabled: true

            onLoadStarted: statustext.text = "Loading..."
            onLoadFinished: statustext.text = "Done loading!"
            onLoadFailed: statustext.text = "Error :("
        }
    }

    Rectangle {
        id: buttons
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: childrenRect.height
        color: "black"
        Row {
            height: okbutton.height
            Button {
                id: okbutton
                label: "OK"
                onClicked: {
                    pleasewait.visible = true
                    api.authenticationCompleted()
                }
            }
            Text {
                id: statustext
                anchors.verticalCenter: parent.verticalCenter
                color: "white"
                text: "ready"
            }
        }
    }


    Rectangle {
        id: pleasewait
        anchors.fill: parent
        color: "black"
        opacity: 0.7
        visible: false
        Text {
            color: "white"
            anchors.centerIn: parent
            text: "Please wait..."
        }
    }
}

