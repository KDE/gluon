import QtQuick 1.0

Rectangle {

       property alias username: usernameLineEdit.text;
       property alias password: passwordLineEdit.text;

       property variant tabTarget: KeyNavigation.right || KeyNavigation.down;
       property variant backtabTarget: KeyNavigation.left || KeyNavigation.up

      property bool providerInitialized: false;
      Keys.onTabPressed: if (tabTarget) tabTarget.focus = true;
      Keys.onBacktabPressed: if (backtabTarget) backtabTarget.focus = true;

       x: 0
       y: 0

       signal clicked

       id: lgn
       border.color: "black"
       color: "darkGrey"

   function providerSet() {
       providerInitialized = true;
   }

   ErrorLabel {
       id: errorLabel;
       // anchors.horizontalCenter: usernameEdit.horizontalCenter;
   }

   Text {
        id: usernameText
        text: qsTr("Username")
        color: "white"
        font.pixelSize: 24
   }


   LineEdit {
        id: usernameLineEdit
        x: 15
        width: usernameText.width * 3
        anchors.top: usernameText.bottom
   }

   Text {
        id: passwordText
        text: qsTr("Password")
        color: "white"
        width: usernameText.width
        font.pixelSize: usernameText.font.pixelSize
        anchors.top: usernameLineEdit.bottom
   }

   LineEdit {
        id: passwordLineEdit
        x: 15
        width: usernameText.width * 3
        anchors.top: passwordText.bottom
        echoMode: TextInput.Password
   }

   // MouseArea {
        // id: mr
        // anchors.fill: parent
        // onClicked: {
            // parent.focus = true
            // lgn.clicked()
        // }
   // }

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
