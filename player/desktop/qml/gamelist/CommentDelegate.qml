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

import QtQuick 1.1
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.core 0.1 as PlasmaCore

Item {
    id: commentDelegateRootItem
    signal replyComment(string parentCommentId)
    width: parent.width
    height: 128

    Rectangle {
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

                Text {
                    height: parent.height
                    width: parent.width - ratingItem.width
                    text: TitleRole
                    font.pointSize: 14
                    elide: Text.ElideRight
                    color: "black"
                }

                RatingItem {
                    id: ratingItem
                    height: parent.height
                    width: height*5
                    rating: RatingRole
                }
            }

            Item {
                id: spacer
                width: parent.width
                height: 6
            }

            Item {
                width: parent.width
                height: parent.rowHeight*4
                clip: true
                Text {
                    width: parent.width
                    text: BodyRole
                    elide: Text.ElideRight
                    maximumLineCount: 100
                    color: "black"
                }
            }

            Row {
                width: parent.width
                height: parent.rowHeight

                Text {
                    height: parent.height
                    width: (parent.width-commentReplyButton.width)/2
                    text: AuthorRole
                    color: "black"
                }

                Text {
                    height: parent.height
                    width: (parent.width-commentReplyButton.width)/2
                    text: DateTimeRole
                    color: "black"
                }

                PlasmaComponents.ToolButton {
                    id: commentReplyButton
                    iconSource: "edit-undo"
                    height: parent.height
                    width: height

                    onClicked: {
                        commentDelegateRootItem.replyComment(ParentIdRole)
                   }
                }
            }
        }
    }
}