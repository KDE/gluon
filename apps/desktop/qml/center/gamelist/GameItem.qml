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

Item {
    id: gameItemRootItem
    width: gamesListView.width
    height: 64
    
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
        color: "black"
    }

    Text{
        anchors.left: gameItemPicture.right
        anchors.top: gameItemTitle.bottom
        anchors.right: playDownloadButton.left
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        text: GameSummary
        color: "black"
    }
    
    /*
    Rating {
        anchors.right: playDownloadButton.left
        anchors.rightMargin: 15
        rate: Rating
    }
    */
    /*
    PlasmaComponents.ToolButton {
        anchors.right: parent.right
        id: playDownloadButton
        height: parent.height
        width: height

        iconSource: Status == GluonPlayer.GameItem.Installed || Status == GluonPlayer.GameItem.Local ? "media-playback-start" : "download"
        onClicked: Status == GluonPlayer.GameItem.Installed || Status == GluonPlayer.GameItem.Local ? mainWindow.playGame(Id) : serviceProvider.downloadGame(Id).startSocialService()
    }
    */
}
