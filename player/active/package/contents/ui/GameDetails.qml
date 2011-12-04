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

Rectangle {
    id: gameDetailsRect
    color: theme.backgroundColor
    opacity: 0.5
    radius: 10

    ListView {
        id: gameDetailsListView

        anchors.fill: parent
        anchors.margins: 20

        clip: true

        model: gameDetailsModel
        delegate: gameDetailsDelegate
    }

    Component {
        id: gameDetailsDelegate

        Column {
            spacing: 20

            Text {
                width: gameDetailsListView.width

                font.pointSize: 12; font.bold: true
                color: theme.textColor
                text: GameName
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                width: gameDetailsListView.width
                wrapMode: Text.WordWrap

                color: theme.textColor
                text: GameDescription
            }
        }
    }
}
