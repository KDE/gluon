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
import Gluon.Player.Desktop 0.72 as GluonPlayer

import "../../utils"

Column {
//     width: parent.width
    spacing: 10
    
    anchors.top: parent.top
    anchors.topMargin: 20
    anchors.left: parent.left
    anchors.leftMargin: 20
    anchors.right: parent.right
    anchors.rightMargin: 20
    
    height: childrenRect.height -20
    
    Text {
        id: gameListTitle
        
        width: parent.width
        text: "Last published"
        font.pointSize: 20
        
        color: design.txcolor
    }
    
    ListView {
        id: gamesListView
        
        width: parent.width
        
        height: childrenRect.height+10
        
        interactive: false
        
        clip: true
        spacing: 10
        model: downloadableGamesModel
        delegate: GameItem { }
    }
}