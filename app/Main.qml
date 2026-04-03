import QtQuick 2.15
import QtQuick.Window
import QtQuick.Dialogs

Window {
    id:root

    width: 740
    height: 480
    visible: true
    title: qsTr("Cypherin")
    color: "black"

    minimumWidth: 740
    maximumWidth: 740
    minimumHeight: 480
    maximumHeight: 480

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

    Loader {
        id: loader
        anchors.fill: parent
        source: "main.qml"
    }

    Rectangle {
        id: rectangle

        property bool clicked: true
        property color basecolor: "lightgreen"

        signal mySignal()

        width: 185
        height: 45

        radius: 5

        color: if (mousearea.containsPress) {
                   return Qt.darker(basecolor)
               } else if (mousearea.containsMouse){
                   return Qt.lighter(basecolor)
                } else {
                   return basecolor
               }

        x:240
        y:150

        Text {
            id: buttonText

            anchors.centerIn: parent

            text: "File en/decrypt"
            font.pixelSize: 14
            font.bold: true
        }

        MouseArea {
            id: mousearea

            anchors.fill: parent

            onClicked: {
                loader.source = "cryption_window.qml"
            }
        }
    }

    Rectangle {
        id: rectangle2

        property bool clicked: true
        property color basecolor2: "lightgray"

        signal mySignal()

        width: 220
        height: 48

        x:280
        y:230
        radius: 5

        color: if (mousearea2.containsPress) {
                   return Qt.darker(basecolor2)
               } else if (mousearea2.containsMouse){
                   return Qt.lighter(basecolor2)
                } else {
                   return basecolor2
               }

        Text {
            id: buttonText2

            anchors.centerIn: parent

            text: "Digital sign & verify"
            font.pixelSize: 14
            font.bold: true
        }

        MouseArea {
            id: mousearea2

            anchors.fill: parent

            hoverEnabled: true

            onClicked: {
                loader.source = "cypher_window.qml"
            }
        }
    }

    Rectangle {
        id: rectangle3

        property bool clicked: true
        property color basecolor3: "lightblue"

        width: 60
        height: 30
        x:660
        y:20

        radius: 50

        color: if (mousearea3.containsPress) {
                   return Qt.darker(basecolor3)
               } else if (mousearea3.containsMouse){
                   return Qt.lighter(basecolor3)
                } else {
                   return basecolor3
               }

        Text {
            id: buttonText3

            anchors.centerIn: parent

            text: "HELP!!"
            font.pixelSize: 13
            font.bold: true
        }

        MouseArea {
            id: mousearea3

            anchors.fill: parent

            hoverEnabled: true

            onClicked: {
                console.log("HELP!!!")
                bridge.openUsage()
            }
        }
    }

    Rectangle {
        id: rectangle4

        property bool clicked: true
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

    Text {
        id: buttonText5

        text: "(The program will crash if u try to perform an operation more than one time)"
        font.pixelSize: 14
        font.bold: true
        color: "gray"

        x: 110
        y: 435
    }
}
