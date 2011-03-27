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

    color: "black";
    anchors.fill: parent;

    Component {
        id: gameItemsDelegate;
        Button {
            id: gameItem;
            width: ListView.view.width;
            icon: "icons/hi32-app-gluon.png";
            text: qsTr(gameName);
            subtext: qsTr(gameDescription);

            onClicked: {
                detailsPage.propagate(gameName, gameDescription, screenshotUrls, status, index);
            }
        }
    }

    ListView {
        width: 200;
        height: 250;
        anchors.fill: parent;
        model: gameItemsModel;
        delegate: gameItemsDelegate;
        spacing: 5;

        header:
            Rectangle {
                color: homePage.color;
                width: ListView.view.width;
                height: moreGames.height + 5;
                Button {
                    id: moreGames;
                    icon: "icons/get-hot-new-stuff.png";
                    text: qsTr("Get More Games");
                    subtext: "5 new games, 16 updated";
                }
            }
    }
}
