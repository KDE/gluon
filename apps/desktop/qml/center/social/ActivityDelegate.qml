 
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

import QtQuick 2.2
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.1
import "../../utils"

Rectangle{
    id: activitydelegate
    width: parent.width
    color: design.midcolor
    
    height: childrenRect.height
    
    Image{
        id: userIcon
        anchors.top: parent.top
        anchors.topMargin:2
        anchors.left:parent.left
        anchors.leftMargin:2
        
        //30 -2 -2 = 26
        width: 60
        height: 60
        
        source: "../../resources/user_64.png"
    }
    
    Desaturate {
        anchors.fill: userIcon
        source: userIcon
        desaturation: 1.0
    }
    
    Text{
        id: signature
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: userIcon.right
        anchors.leftMargin: 10
        
        font.pixelSize: 11
        
        font.bold: true
        
        text: firstname + " " + lastname
        
        color: design.txcolor
    }
    
    Text{
        anchors.top: signature.bottom
        anchors.topMargin: 10
        anchors.left: userIcon.right
        anchors.leftMargin: 20
        
        font.pixelSize: 14
        
        text: message
        
        color: design.txcolor
    }
}