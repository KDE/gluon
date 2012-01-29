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
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.mobilecomponents 0.1 as MobileComponents
import org.kde.plasma.core 0.1 as PlasmaCore

Item {
    width: parent.width
    height: 128

    PlasmaCore.FrameSvgItem {
        id: surfaceNormal

        anchors.fill: parent
        anchors.leftMargin: DepthRole*20
        imagePath: "widgets/button"
        prefix: "normal"

        Column {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 2
            property real rowHeight: height/3 - 2*spacing

            Row {
                width: parent.width
                height: parent.rowHeight

                PlasmaComponents.Label {
                    height: parent.height
                    width: parent.width - ratingItem.width
                    text: TitleRole
                }

                //Use Rating Item
                PlasmaComponents.Label {
                    id: ratingItem
                    height: parent.height
                    width: 10
                    text: RatingRole
                }
            }

            Row {
                width: parent.width
                height: parent.rowHeight

                PlasmaComponents.TextArea {
                    height: parent.height
                    width: parent.width
                    readOnly: true
                    text: BodyRole
                }
            }

            Row {
                width: parent.width
                height: parent.rowHeight

                PlasmaComponents.Label {
                    height: parent.height
                    width: parent.width/2
                    text: AuthorRole
                }

                PlasmaComponents.Label {
                    height: parent.height
                    width: parent.width/2
                    text: DateTimeRole
                }
            }
        }
    }
}