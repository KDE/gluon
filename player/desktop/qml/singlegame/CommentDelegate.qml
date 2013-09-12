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
import org.kde.plasma.core 0.1 as PlasmaCore

Column {
    id: commentDelegateRootItem
    width: parent.width
	
	Text{
		anchors.top: parent.top
		anchors.left: parent.left
		id: commentdelegate_title
		font.bold : true
		text: title
	}
	
	Text{
		id: commentdelegate_author
		anchors.right: parent.right
		anchors.bottom: commentdelegate_title.bottom
		anchors.leftMargin: 10
		color: "gray"
		text: "written by "+author
	}
	
	Text{
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.top: commentdelegate_title.bottom
			anchors.topMargin: 5
			anchors.leftMargin: 20
			wrapMode: Text.WordWrap
			font.pixelSize: 13
			text: body
	}
}