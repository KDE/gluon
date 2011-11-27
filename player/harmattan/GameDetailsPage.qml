/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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
import GluonPlayerGameViewItem 1.0
import com.nokia.meego 1.1
import com.nokia.extras 1.1

Page {

    id: gameDetailsPage;
    color: "black";
    anchors.fill: parent;

    property int gameIndex;

    function propagate(projectName, projectDescription, screenshotUrls, status, index) {
        if (status == GameViewItem.Downloadable) {
            play_game_btn.text = qsTr("Download " + projectName);
            play_game_btn.icon = "icons/download.png";
        } else if (status == GameViewItem.Installed) {
            play_game_btn.text = qsTr("Play " + projectName);
            play_game_btn.icon = "icons/media-playback-start.png";
        } else if (status == GameViewItem.Upgradable) {
            play_game_btn.text = qsTr("Upgrade " + projectName);
            play_game_btn.icon = "system-software-update.png";
        }

        read_author_desc_btn.subtext = qsTr(projectDescription);
        previewImages.model = screenshotUrls;
        gameIndex = index;
        mainview.statepoint = "details";
    }

    ListView {
        id: gameItemsListView;

        anchors.fill: parent;
        model: GameDetailsModel {}

        delegate: ListDelegate {
            iconSource: iconPath;
            titleText: text;
            subtitleText: subtext;
            drillDownArrow: true;
        }
    }

    ToolBarLayout {
        id: tabTools

        ToolIcon { iconId: "toolbar-back"; onClicked: { colorMenu.close(); pageStack.pop(); }  }
    }
}
