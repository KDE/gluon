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

import QtQuick 2.2
import QtQuick.Controls 1.1

import "../../utils"


Column{
    id: addCommentForm
    width: parent.width
    signal addComment(string parentId)
    property alias subjectText: commentSubjectText.text;
    property alias bodyText: commentBodyText.text;
    property string parentId;
    
    function checkLog(){
        if(serviceProvider.isLoggedIn == true){
            commentSubjectText.readOnly = false
            commentBodyText.readOnly = false
            commentButton.text = "Send"
        } else {
            commentSubjectText.readOnly = true
            commentBodyText.readOnly = true
            commentButton.text = "Log in to send"
        }
    }
    
    Component.onCompleted:{
        checkLog();
        serviceProvider.loginFinished.connect(checkLog)
    }
    
    TextField {
        id: commentSubjectText
        height: 32; width: parent.width
        placeholderText: "Subject"
        style: DesignTextField{}
        readOnly: true
    }
    TextArea {
        id: commentBodyText
        height: 300
        width: parent.width
        backgroundVisible: false
        //placeholderText: "write your comment here"
        readOnly: true
    }
    Button {
        id: commentButton
        text: "Send"
        width: parent.width
        style: DesignButton{}
        onClicked:{
            parent.addComment(parent.parentId);
        }
    }
}
 
