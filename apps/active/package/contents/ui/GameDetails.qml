/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
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
import org.kde.gluon.playercomponents 1.0 as Gluon

Rectangle {
    id: gameDetailsRect
    property alias gameId: gameMetadata.gameId

    radius: 10

    Gluon.GameMetadata
    {
        id: gameMetadata
    }

    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        Text {
            width: parent.width

            font.pointSize: 12; font.bold: true
            text: gameMetadata.gameName
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            width: parent.width
            wrapMode: Text.WordWrap

            text: gameMetadata.gameDescription
        }
    }
}
