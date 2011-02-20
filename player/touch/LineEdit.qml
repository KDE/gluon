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

/**
 * A LineEdit in Gluon style
 */

FocusScope {
    property alias text: textInput.text;
    property alias labelText: label.text;
    property alias echoMode: textInput.echoMode;
    property variant tabTarget: KeyNavigation.down;
    property variant backtabTarget: KeyNavigation.up;

    height: 50;
    anchors {
        margins: 5;
    }

    Keys.onTabPressed: if (tabTarget) tabTarget.focus = true;
    Keys.onBacktabPressed: if (backtabTarget) backtabTarget.focus = true;

    onActiveFocusChanged: {
        if (activeFocus)
            textInput.selectAll();
    }

    BorderImage {
        anchors.fill: parent;

        source: "icons/lineedit.png"
        border.bottom: 20;
        border.top: 20;
        border.right: 20;
        border.left: 20;
    }

    Text {
        id: label;
        x: textInput.x;
        y: textInput.y;
        color: "darkGray";
        font: textInput.font;

        states: [
            State {
                name: "labelHidden";
                when: textInput.text != "";
                PropertyChanges { target: label; opacity: 0; }
            }
        ]
        transitions: [
            Transition {
                from: "labelHidden";
                NumberAnimation {
                    property: "opacity";
                    easing.type: Easing.InOutQuad;
                }
            }
        ]
    }

    TextInput {
        id: textInput;

        y: 5;
        anchors {
            verticalCenter: parent.verticalCenter;
            verticalCenterOffset: 2;
            right: parent.right;
            rightMargin: 12;
            left: parent.left;
            leftMargin: 12;
        }

        focus: true;

        selectByMouse: true;
        passwordCharacter: "*";

        font.pixelSize: 24;
    }
}
