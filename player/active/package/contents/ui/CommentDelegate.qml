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
    id: commentDelegateRootItem
    property QtObject addCommentForm
    width: parent.width
    height: 128

    PlasmaBackground {
        id: surfaceNormal

        anchors.fill: parent
        anchors.leftMargin: DepthRole*20

        Column {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 2
            property real rowHeight: height/5 - 2*spacing

            Row {
                width: parent.width
                height: parent.rowHeight

                PlasmaComponents.Label {
                    height: parent.height
                    width: parent.width - ratingItem.width
                    text: TitleRole
                }

                RatingItem {
                    id: ratingItem
                    height: parent.height
                    width: height*5
                    rating: RatingRole
                }
            }

            PlasmaComponents.TextArea {
                width: parent.width
                height: parent.rowHeight*4
                wrapMode: TextEdit.Wrap
                readOnly: true
                text: BodyRole
            }

            Row {
                width: parent.width
                height: parent.rowHeight

                PlasmaComponents.Label {
                    height: parent.height
                    width: (parent.width-commentReplyButton.width)/2
                    text: AuthorRole
                }

                PlasmaComponents.Label {
                    height: parent.height
                    width: (parent.width-commentReplyButton.width)/2
                    text: DateTimeRole
                }

                PlasmaComponents.ToolButton {
                    id: commentReplyButton
                    iconSource: "edit-undo"
                    height: parent.height
                    width: height

                    onClicked: {
                        commentDelegateRootItem.addCommentForm.parentId = ParentIdRole
                        commentDelegateRootItem.addCommentForm.open()
                    }
                }
            }
        }
    }
}