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

    signal clicked

    border.color: "black"
    color: "darkGrey"

     Component {
         id: registrationDelegate
         Item {
             width: parent.width; height: 40
                Row {
                    spacing: 0
                    Text {
                        id: identifierText
                        text: textdata
                        color: "white"
                        font.pixelSize: 24
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignVCenter
                        width: registrationDelegate.width/4
                    }

                    LineEdit {
                        id: identifierLineEdit
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
     }

   // MouseArea {
        // id: regmr
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
