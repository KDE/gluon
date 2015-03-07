import QtQuick 2.3

Rectangle {
    width: 200
    height: 100
    color: "red"


    Rectangle {
        anchors.centerIn: parent
        width: 100
        height: 50
        color: "dark red"


        MouseArea {
            anchors.fill: parent
            onClicked: { parent.color = "green"; }
            onWheel: { console.log("blub"); parent.color = "light blue"; }
        }

        Text {
            anchors.centerIn: parent
            text: "Hello, World!"
        }
    }
}

