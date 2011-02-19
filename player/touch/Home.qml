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
    anchors.fill: parent

    Component {
        id: gameItemsDelegate
        Item {
            height: Math.max(playButtonIcon.height, gameIcon.height) + 10;
            width: ListView.view.width;
            Image {
                id: gameIcon;
                anchors.verticalCenter: parent.verticalCenter;
                source: "icons/hi32-app-gluon.png";
            }

            Text {
                id: gameViewName;
                text: qsTr(gameName);
                anchors {
                    verticalCenter: parent.verticalCenter / 2;
                    left: gameIcon.right;
                }
            }

            Text {
                id: gameViewDescription;
                text: qsTr(gameDescription);
                anchors {
                    verticalCenter: parent.verticalCenter * 1.5;
                    top: gameViewName.botton;
                    left: gameIcon.right;
                }
            }

            Image {
                id: playButtonIcon;
                source: "icons/media-playback-start.png";
                anchors {
                    left: gameViewName.right;
                    verticalCenter: parent.verticalCenter;
                }
                MouseArea {
                    id: playButtonMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        gameWindowManager.setProject(index);
                    }
                }
            }
        }
    }

    ListView {
        width: 200;
        height: 250;
        anchors.fill: parent;
        model: gameItemsModel;
        delegate: gameItemsDelegate;

        header: Button {
            id: new_user
            /* width: parent.width / 4 */
            height: parent.height * 1 / 10;
            icon: "icons/get-hot-new-stuff.png";
            text: qsTr("Get More Games");
            subtext: "5 new games, 16 updated";
            onClicked: console.log("this doesn't do anything yet...");
        }
    }
}
