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

 
Item {
    id: gameItemRootItem
    anchors.horizontalCenter: parent.horizontalCenter
    
    
    width: gamesListView.width -6
    height: 64
    
    Rectangle {
        anchors.left: parent.left
        anchors.leftMargin: -3
        anchors.right: parent.right
        anchors.rightMargin: -3
        anchors.top: parent.top
        anchors.topMargin: -3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -3
            
        color: design.midcolor
        radius: 5
        
        z:-1
    }
    
    MouseArea{
        anchors.fill: parent
        onClicked:{
            centralBox.showSingleGame(Id);
        }
    }
    
    Image {
        id: gameItemPicture
        anchors.left: parent.left
        source: PreviewPicture
        height: parent.height
        width: height
    }

    Text{
        anchors.top: parent.top
        anchors.left: gameItemPicture.right
        anchors.leftMargin: 5
        id: gameItemTitle
        text: GameName
        color: design.txlkcolor
        
        font.pointSize: 14
        font.bold: true
        
    }

    Text{
        anchors.left: gameItemPicture.right
        anchors.top: gameItemTitle.bottom
        anchors.right: playDownloadButton.left
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        text: GameSummary
        color: design.txcolor
        
        wrapMode: Text.WordWrap
    }
    
    
    Rating {
        anchors.right: playDownloadButton.left
        anchors.rightMargin: 15
        rate: Rating
    }
    
    
    Image {
        anchors.right: parent.right
        id: playDownloadButton
        height: parent.height
        width: height
        
        source: Status == GluonPlayer.GameItem.Installed || Status == GluonPlayer.GameItem.Local ? "../../resources/play_128.png" : "../../resources/download_128.png"
        
        MouseArea{
            anchors.fill: parent
            onClicked: Status == GluonPlayer.GameItem.Installed || Status == GluonPlayer.GameItem.Local ? mainWindow.playGame(Id) : serviceProvider.downloadGame(Id).startSocialService()
        }
    }
}