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
    Button {
        id: new_user
        /* width: parent.width / 4 */
        /* height: parent.height * 1 / 5 */
        icon: "icons/get-hot-new-stuff.png"
        text: qsTr("Get More Games")
        subtext: "5 new games, 16 updated"
        onClicked: console.log("this doesn't do anything yet...")
    }

    Component {
        id: gameItemsDelegate
        Item {
            Image {
                source: "icons/hi32-app-gluon.png"
            }
            Text { text: gameName }
            Text { text: gameDescription }
            Image {
                source: "icons/media-playback-start.png"
            }
        }
    }

    ListView {
        width: 200; height: 250
        anchors.fill: parent
        model: gameItemsModel
        delegate: gameItemsDelegate
    }
}
