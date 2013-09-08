/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

Item {
    id: root;
    width: 500;
    height: 500;

    property bool ignoreFirst: true;

    Text {
        id: title;
        anchors {
            top: parent.top;
            topMargin: parent.height / 4;
            horizontalCenter: parent.horizontalCenter;
        }

        color: "#339933";

        text: "Electron Apocalypse";

        font {
            bold: true;
            pointSize: 20;
            capitalization: Font.SmallCaps;
        }
    }

    ListView {
        id: buttons;

        anchors {
            top: title.bottom;
            topMargin: 40;
            horizontalCenter: parent.horizontalCenter;
            bottom: parent.bottom;
            bottomMargin: 40;
        }

        width: parent.width / 2;

        spacing: 20;
        currentIndex: 0;

        keyNavigationWraps: true;

        model: buttonModel;
        delegate: buttonDelegate;
    }

    Rectangle {
        id: help;
        anchors.fill: parent;

        anchors {
            topMargin: 20;
            leftMargin: 20;
            rightMargin: 20;
            bottomMargin: 20;
        }

        color: "#339933";

        opacity: 0;
        Behavior on opacity {
            NumberAnimation { duration: 250 }
        }

        Text {
            id: helpText;

            anchors.centerIn: parent;
            color: "#990000";

            text: "<h2>Controls</h2><ul>" +
            "<li>ASDF: Navigate around the world</li>" +
            "<li>Mouse movement: Move the crosshair</li>" +
            "<li>Mouse click: Shoot</li>";
        }

        Text {
            anchors {
                horizontalCenter: parent.horizontalCenter;
                bottom: parent.bottom;
                bottomMargin: 20;
            }

            SequentialAnimation on color {
                loops: Animation.Infinite;
                ColorAnimation { to: "#990000"; duration: 1000; }
                ColorAnimation { to: "#339933"; duration: 1000; }
            }
            opacity: 1.0;
            font {
                bold: true;
                pointSize: 16;
            }

            text: "Close";

            MouseArea {
                anchors.fill: parent;
                onPressed: help.opacity = 0;
            }
        }
    }

    ListModel {
        id: buttonModel;

        ListElement {
            buttonText: "New Game";
            buttonTriggered: "Game.setCurrentScene(\"Apocalypse/Scenes/Level 1\");"
        }

        ListElement {
            buttonText: "How to Play";
            buttonTriggered: "help.opacity = 1;"
        }

        ListElement {
            buttonText: "Quit Game";
            buttonTriggered: "Game.stopGame();"
        }
    }

    Component {
        id: buttonDelegate;

        Text {
            id: button;

            anchors.horizontalCenter: parent.horizontalCenter;

            color: "#339933";
            SequentialAnimation on color {
                running: button.state == "Current";
                loops: Animation.Infinite;
                ColorAnimation { to: "#990000"; duration: 1000; }
                ColorAnimation { to: "#339933"; duration: 1000; }
            }
            font.pointSize: 18;

            focus: ListView.isCurrentItem;

            text: buttonText;

            MouseArea {
                anchors.fill: parent;
                onPressed: eval(buttonTriggered);
            }

            states: [
                State {
                    name: "Current";
                    when: ListView.isCurrentItem;
                    PropertyChanges { target: button; color: "#990000" }
                }
            ]

            function trigger() {
                eval(buttonTriggered);
            }
        }
    }

    function update() {
        if(GameObject.Key_Down.isActionStarted()) {
            buttons.incrementCurrentIndex();
        }
        if(GameObject.Key_Up.isActionStarted()) {
            buttons.decrementCurrentIndex();
        }
        if(GameObject.Key_Enter.isActionStarted()) {
            if(help.opacity > 0)
            {
                help.opacity = 0;
            }
            else
            {
                if(root.ignore)
                {
                    root.ignore = false;
                }
                else
                {
                    buttons.currentItem.trigger();
                }
            }
        }
    }
}
