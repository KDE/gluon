/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
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

import QtQuick 1.1
import org.kde.plasma.components 0.1 as PlasmaComponents

PlasmaComponents.Dialog {
    id: addCommentFormDialog
    property string parentId
    property alias subjectText: commentSubjectText.text
    property alias bodyText: commentBodyText.text
    width: 512; height: 256

    buttons: PlasmaComponents.Button {
        id: postButton
        height: 32; width: addCommentFormDialog.width
        text: "Post"
        onClicked: addCommentFormDialog.accept()
    }
    content: Column {
        height: addCommentFormDialog.height - postButton.height; width: addCommentFormDialog.width
        PlasmaComponents.TextField {
            id: commentSubjectText
            height: 32; width: parent.width
            placeholderText: "Subject"
        }
        PlasmaComponents.TextArea {
            id: commentBodyText
            height: addCommentFormDialog.height - commentSubjectText.height - postButton.height
            width: parent.width
            placeholderText: "Body"
        }
    }
}