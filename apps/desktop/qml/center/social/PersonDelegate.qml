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
    id: persondelegate
    width: parent.width
    color: design.midcolor
    
    height:30
    
    property string m_id : personid;
    property string m_name : firstname;
    property string m_surname : lastname;
    
    Image{
        id: userIcon
        anchors.top: parent.top
        anchors.topMargin:2
        anchors.left:parent.left
        anchors.leftMargin:2
        anchors.bottom:parent.bottom
        anchors.bottomMargin:2
        
        //30 -2 -2 = 26
        width: 26
        
        source: "../../resources/user_64.png"
    }
    
    Desaturate {
        anchors.fill: userIcon
        source: userIcon
        desaturation: 1.0
    }
    
    Text{
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: userIcon.right
        anchors.leftMargin: 10
        
        font.pixelSize: 20
        
        text: firstname + " " + lastname + " (" + personid + ")"
        
        color: design.txcolor
    }
    
    Button{
        anchors.right: parent.right
        anchors.rightMargin: 3
        anchors.verticalCenter: parent.verticalCenter
        
        text: "Profile"
        
        onClicked:{
            profilescreen.username = persondelegate.m_id;
            profilescreen.name = persondelegate.m_name;
            profilescreen.surname = persondelegate.m_surname;
            profilescreen.open();
        }
        
        style: DesignButton{}
    }
    
}