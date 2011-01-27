/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

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
