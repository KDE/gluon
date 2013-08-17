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
import org.kde.plasma.extras 0.1 as PlasmaExtras
import org.kde.qtextracomponents 0.1 as QtExtraComponents
import Gluon.Player.Desktop 0.72 as GluonPlayer

Item {
    id: gameItemRootItem
    width: gamesListView.width
    height: 64


	Image {
		id: gameItemPicture
		anchors.left: parent.left
		source: PreviewPicture
		height: parent.height
		width: height
	}

	PlasmaExtras.Title{
		anchors.top: parent.top
		anchors.left: gameItemPicture.right
		anchors.leftMargin: 5
		id: gameItemTitle
		text: GameName
		color: "black"
	}

	PlasmaComponents.Label{
		anchors.left: gameItemPicture.right
		anchors.top: gameItemTitle.bottom
		anchors.leftMargin: 5
		text: GameSummary
		color: "black"
		width: 100
	}

	Rating {
		anchors.right: playDownloadButton.left
		anchors.rightMargin: 15
		rate: Rating
	}

	PlasmaComponents.ToolButton {
		anchors.right: parent.right
		id: playDownloadButton
		height: parent.height
		width: height

		iconSource: Status == GluonPlayer.GameItem.Installed || Status == GluonPlayer.GameItem.Local ? "media-playback-start" : "download"
		onClicked: Status == GluonPlayer.GameItem.Installed || Status == GluonPlayer.GameItem.Local ? mainWindow.playGame(Id) : serviceProvider.downloadGame(Id).startSocialService()
	}
}
