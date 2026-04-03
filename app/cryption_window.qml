import QtQuick
import QtQuick.Controls

Window {
    id:cryption

    width: 740
    height: 480
    visible: true
    title: qsTr("File en/decryption")
    color: "black"

    minimumWidth: 740
    maximumWidth: 740
    minimumHeight: 480
    maximumHeight: 480

    signal call_cryption(string action)

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
        text: "Please place all the files to be encrypted/decrypted in 'files' folder in the backend"
        color: "white"
        font.pixelSize: 16
        font.bold: true

        x: 52
        y: 50
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
        id: cryption_box

        x: 290
        y: 235
        width: 150

        model: ["encrypt", "decrypt"]

        font.bold: true
        font.pixelSize: 15
    }

    Text {
        text: "the files?"
        color: "white"
        font.pixelSize: 20
        font.bold: true

        x: 449
        y: 232
    }

    Rectangle {
        id: rectangle2

        property color basecolor: "gray"

        width: 200
        height: 40
        radius: 7

        color: if (mousearea2.containsPress) {
                   return Qt.darker(basecolor)
               } else if (mousearea2.containsMouse){
                   return Qt.lighter(basecolor)
                } else {
                   return basecolor
               }

        x:263
        y:280

        Text {
            id: buttonText2

            anchors.centerIn: parent

            text: "perform the action?"
            font.pixelSize: 14
            font.bold: true
            color: "black"
        }

        MouseArea {
            id: mousearea2

            anchors.fill: parent

            onClicked: {
                bridge.callC_main(cryption_box.currentText)
            }
        }
    }

    Rectangle {
        id: exit_rectangle

        property color basecolor4: "black"

        width: 40
        height: 40

        color: if (mousearea4.containsPress) {
                   return Qt.darker(basecolor4)
               } else if (mousearea4.containsMouse){
                   return Qt.lighter(basecolor4)
                } else {
                   return basecolor4
               }

        x:700
        y:435

        Text {
            id: buttonText4

            anchors.centerIn: parent

            text: ">"
            font.pixelSize: 18
            font.bold: true
            color: "white"
        }

        MouseArea {
            id: mousearea4

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
