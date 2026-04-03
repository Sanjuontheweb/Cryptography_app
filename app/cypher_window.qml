import QtQuick
import QtQuick.Controls

Window {
    id:cypher

    width: 740
    height: 480
    visible: true
    title: qsTr("Digital sign/verify")
    color: "black"

    minimumWidth: 740
    maximumWidth: 740
    minimumHeight: 480
    maximumHeight: 480

    signal call_cypher(string action)

    MouseArea {
        anchors.fill: parent
    }

    Image {
        id: wallpaper

        anchors.fill: parent
        source: "resources/wallpaper.jpg"
        width: 1920
        height: 1080
    }

    Text {
        text: "Please place one file inside files to sign/verify"
        color: "white"
        font.pixelSize: 20
        font.bold: true

        x: 130
        y: 90
    }

    Text {
        text: "do you wanna"
        color: "white"
        font.pixelSize: 20
        font.bold: true

        x: 150
        y: 230
    }

    ComboBox {
        id: cypher_box

        x: 290
        y: 235
        width: 150

        model: ["sign", "verify"]

        font.bold: true
        font.pixelSize: 15
    }

    Text {
        text: "the file?"
        color: "white"
        font.pixelSize: 20
        font.bold: true

        x: 449
        y: 232
    }

    Rectangle {
        id: perform_rectangle

        property color basecolor: "gray"

        width: 200
        height: 40

        radius: 7

        color: if (mousearea.containsPress) {
                   return Qt.darker(basecolor)
               } else if (mousearea.containsMouse){
                   return Qt.lighter(basecolor)
                } else {
                   return basecolor
               }

        x:263
        y:280

        Text {
            id: buttonText

            anchors.centerIn: parent

            text: "perform the action?"
            font.pixelSize: 14
            font.bold: true
            color: "black"
        }

        MouseArea {
            id: mousearea

            anchors.fill: parent

            onClicked: {
                bridge.callS_main(cypher_box.currentText)
            }
        }
    }

    Rectangle {
        id: exit_rectangle

        property color basecolor2: "black"

        width: 40
        height: 40

        color: if (mousearea2.containsPress) {
                   return Qt.darker(basecolor2)
               } else if (mousearea2.containsMouse){
                   return Qt.lighter(basecolor2)
                } else {
                   return basecolor2
               }

        x:700
        y:435

        Text {
            id: buttonText2

            anchors.centerIn: parent

            text: ">"
            font.pixelSize: 18
            font.bold: true
            color: "white"
        }

        MouseArea {
            id: mousearea2

            anchors.fill: parent

            onClicked: {
                Qt.quit()
                console.log("Thankin you")
            }
        }
    }

    Connections {
        target: bridge
    }
}
