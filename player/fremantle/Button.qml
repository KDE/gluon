/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

/**
 * A Button in gluon style
 */

Rectangle {
       id: button

       property string text;
       property string subtext;
       property string icon;
       property int textfontsize: 20;
       property int subtextfontsize: 14;
       property alias enabled: buttonMouseArea.enabled;
       property variant tabTarget: KeyNavigation.right || KeyNavigation.down;
       property variant backtabTarget: KeyNavigation.left || KeyNavigation.up;
       signal clicked;

       border.color: "black";
       color: "darkGrey";

       Keys.onTabPressed: if (tabTarget) tabTarget.focus = true;
       Keys.onBacktabPressed: if (backtabTarget) backtabTarget.focus = true;

       height: Math.max(pix.height, textelement.height + subtextelement.height) + 10;
       width: parent.width;

   QtObject {
       id: priv;
       property bool spaceDown: false;
   }

    BorderImage {
        id: buttonBorderImage;
    }

   Image {
        id: pix;
        source: parent.icon;
        anchors {
            left: parent.left;
            verticalCenter: parent.verticalCenter;
            margins: 10;
        }
   }

   Column {
       id: textContainer
       anchors.verticalCenter: parent.verticalCenter
       anchors {
           left: pix.right;
           right: parent.right;
           leftMargin: 5;
           rightMargin: 5;
       }

       Text {
            id: textelement;
            text: button.text;
            width: parent.width;
            color: "white";
            font.pixelSize: button.textfontsize;
            elide: Text.ElideRight;
       }

       Text {
            id: subtextelement;
            text: button.subtext;
            width: parent.width;
            color: "white";
            font.pixelSize: button.subtextfontsize;
            elide: Text.ElideRight;
       }
   }

   MouseArea {
        id: buttonMouseArea;
        anchors.fill: parent;
        hoverEnabled: true;
        onClicked: {
            parent.focus = true;
            parent.clicked();
        }
   }

    states: [
        State {
            name: "pressed";
            when: enabled && ((buttonMouseArea.containsMouse
                              && buttonMouseArea.pressed)
                  || priv.spaceDown);
            PropertyChanges {
                target: buttonBorderImage;
                // source: "icons/buttonpressed.png";
            }

             PropertyChanges {
                target: textContainer;
                anchors {
                    horizontalCenterOffset: 1;
                    verticalCenterOffset: 1;
                }
              }
           },

      State {
        name: "hovered"
          when: enabled && ((buttonMouseArea.containsMouse && !buttonMouseArea.pressed)
                  || parent.activeFocus);
      PropertyChanges {
            target: buttonBorderImage;
            // source: "icons/buttonhovered.png";
      }
                 },

      State {
          name: "disabled";
          when: !enabled;
          PropertyChanges {
            target: buttonBorderImage;
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
            // properties: "x,left";
            // easing.type: Easing.InOutQuad;
            // duration: 200;
        // }
    // }
}

