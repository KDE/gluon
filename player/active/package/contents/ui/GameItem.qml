/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

import QtQuick 1.0
import org.kde.qtextracomponents 0.1
import org.kde.plasma.mobilecomponents 0.1 as MobileComponents

Item {
    id: gameItemRootItem
    width: gamesListView.width
    height: 64

    ListView.onAdd:
        SequentialAnimation {
            PropertyAction { target: gameItemRootItem; property: "height" ; value: 0 }
            NumberAnimation { target: gameItemRootItem; property: "height"; to: 64; duration: 500;
                easing.type: Easing.InOutQuad }
        }

    Rectangle {
        color: "white"
        opacity: 0.5
        radius: 10
        anchors.fill:
        gameItemRow
    }

    Row {
        id: gameItemRow
        anchors.fill: parent

        spacing: 10

        MobileComponents.IconButton {
            id: iconButton
            height: parent.height
            width: height
            icon: QIcon("gluon-player")
        }

        Text {
            height: parent.height
            width: parent.width - iconButton.width

            verticalAlignment: Text.AlignVCenter

            text: GameName
        }
    }

    MouseArea {
        anchors.fill: gameItemRow

        onClicked: {
            rootItem.currentGameId = Id;
        }
    }
}
