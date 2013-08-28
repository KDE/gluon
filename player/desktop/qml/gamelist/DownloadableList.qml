 
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
import Gluon.Player.Desktop 0.72 as GluonPlayer

import ".."
import "../highlights"

Item {
    
	anchors.bottom: parent.bottom
	
	BackgroundBox{ target: hlBox; }
	
	HighlightBox{
		id: hlBox
	}
	
	BackgroundBox{ target: gameListItem; }
	
	width: parent.width
	
	Item {
		id: gameListItem
		
		anchors.top: hlBox.bottom;
		anchors.topMargin: 40
		
		anchors.bottomMargin: 20;
		anchors.bottom: parent.bottom;
		
		width: parent.width
		
		Row {
			anchors.fill: parent
			anchors.margins: 20
			spacing: 10

			Column {
				height: parent.height
				width: parent.width
				spacing: 20

				PlasmaExtras.Title {
					id: gameListTitle
					height: 32
					width: gamesListView.width
					text: "Last published"
				}
				
				ListView {
					id: gamesListView

					height: parent.height - gameListTitle.height
					width: parent.width
					
					clip: true
					spacing: 10
					model: downloadableGamesModel
					delegate: GameItem { }
				}
			}
		}
	}
}