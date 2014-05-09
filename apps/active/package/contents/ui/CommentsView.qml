/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2012 Shantanu Tushar <shaan7in@gmail.com>
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
import org.kde.gluon.playercomponents 1.0 as Gluon

ListView {
    id: commentsListView
    property alias gameId: commentsModel.gameId

    model: Gluon.CommentItemsModel { id: commentsModel }
    delegate: CommentDelegate {
        onReplyComment: {
            commentForm.parentId = parentCommentId
            commentForm.open()
        }
    }

    spacing: 10
    clip: true

    AddCommentForm {
        id: commentForm
        property string parentId
        onAccepted: commentsModel.uploadComment(parentId, commentForm.subjectText, commentForm.bodyText );
    }
}
