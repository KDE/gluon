import QtQuick 1.0

Rectangle {

       id: btn
       clip: true

       property string text
       property string subtext
       property string icon
       signal clicked

       border.color: "black"
       color: "darkGrey"

   Image {
        id: pix
        source: btn.icon
   }

   Text {
        id: textelement
        text: btn.text
        color: "white"
        font.pixelSize: btn.height * 2/5
        anchors.left: pix.right
   }

   Text {
        id: subtextelement
        text: btn.subtext
        color: "white"
        font.pixelSize: btn.height * 2/5
        anchors.left: pix.right
        anchors.top: textelement.bottom
   }

   MouseArea {
        id: mr
        anchors.fill: parent
        onClicked: {
            parent.focus = true;
            btn.clicked()
        }
   }

   states: State {
        name: "pressed"; when: mr.pressed
        PropertyChanges { target: textelement; x: 5 }
        PropertyChanges { target: pix; x: textelement.x + textelement.width + 3 }
   }

    transitions: Transition {
        NumberAnimation {
            properties: "x,left"
            easing.type: Easing.InOutQuad
            duration: 200
        }
    }
}
