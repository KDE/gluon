import QtQuick 1.0

/**
 * A Button in gluon style
 */

Rectangle {

       // clip: true

       id: button

       property string text
       property string subtext
       property string icon
       property alias enabled: buttonMouseArea.enabled
       property variant tabTarget: KeyNavigation.right || KeyNavigation.down;
       property variant backtabTarget: KeyNavigation.left || KeyNavigation.up;
       signal clicked

       border.color: "black"
       color: "darkGrey"

       Keys.onTabPressed: if (tabTarget) tabTarget.focus = true;
       Keys.onBacktabPressed: if (backtabTarget) backtabTarget.focus = true;

   QtObject {
       id: priv;
       property bool spaceDown: false;
   }

    BorderImage {
        id: buttonBorderImage
    }

   Image {
        id: pix
        source: parent.icon
   }

   Text {
        id: textelement
        text: parent.text
        color: "white"
        font.pixelSize: parent.height * 2/5
        anchors.left: pix.right
   }

   Text {
        id: subtextelement
        text: parent.subtext
        color: "white"
        font.pixelSize: parent.height * 2/5
        anchors.left: pix.right
        anchors.top: textelement.bottom
   }

   MouseArea {
        id: buttonMouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            parent.focus = true
            parent.clicked()
        }
   }

    states: [
        State {
            name: "pressed"
            when: enabled && ((buttonMouseArea.containsMouse && buttonMouseArea.pressed)
                  || priv.spaceDown);
            PropertyChanges {
                target: buttonBorderImage
                // source: "icons/buttonpressed.png";
            }

             PropertyChanges {
                target: textelement
                anchors.horizontalCenterOffset: 1
                anchors.verticalCenterOffset: 1
              }
           },

      State {
        name: "hovered"
          when: enabled && ((buttonMouseArea.containsMouse && !buttonMouseArea.pressed)
                  || button.activeFocus);
      PropertyChanges {
            target: buttonBorderImage
            // source: "icons/buttonhovered.png";
      }
                 },

      State {
            name: "disabled"
          when: !enabled
          PropertyChanges {
            target: buttonBorderImage
            // source: "icons/buttondisabled.png";
          }

      PropertyChanges {
        target: textelement;
        opacity: 0.7;
      }
                 }
       ]

    // transitions: Transition {
        // NumberAnimation {
            // properties: "x,left"
            // easing.type: Easing.InOutQuad
            // duration: 200
        // }
    // }
}
