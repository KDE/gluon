import QtQuick 1.0

Rectangle {

       x: 0
       y: 0

       signal clicked

       id: lgn
       border.color: "black"
       color: "darkGrey"


     Component {
         id: registrationDelegate
         Item {
             width: 180; height: 40
                Column {
                    Text {
                        id: identifierText
                        text: textdata
                        color: "white"
                        font.pixelSize: 24
                    }

                    LineEdit {
                        id: identifierLineEdit
                        x: 15
                        width: identifierText.width * 3
                   }
               }
         }
     }

     ListView {
         anchors.fill: parent
         model: RegistrationModel {}
         delegate: registrationDelegate
         highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
         focus: true
     }

   MouseArea {
        id: regmr
        anchors.fill: parent
        onClicked: {
            // parent.focus = true
            // lgn.clicked()
        }
   }

   states: State {
        name: "pressed"; when: mr.pressed
        // PropertyChanges { target: textelement; x: 5 }
        // PropertyChanges { target: pix; x: textelement.x + textelement.width + 3 }
   }

    transitions: Transition {
        NumberAnimation {
            // properties: "x,left"
            easing.type: Easing.InOutQuad
            duration: 200
        }
    }
}
