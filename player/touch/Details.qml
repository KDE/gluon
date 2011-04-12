/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

import QtQuick 1.0
import GluonPlayerGameViewItem 1.0

Rectangle {

    color: "black";
    anchors.fill: parent;

    property int gameIndex;

    function propagate(gameName, gameDescription, screenshotUrls, status, index) {
		if (status == GameViewItem.Downloadable) {
        	play_game_btn.text = qsTr("Download " + gameName);
        	play_game_btn.icon = "icons/download.png";
        } else if (status == GameViewItem.Installed) {
        	play_game_btn.text = qsTr("Play " + gameName);
        	play_game_btn.icon = "icons/media-playback-start.png";
        } else if (status == GameViewItem.Upgradable) {
        	play_game_btn.text = qsTr("Upgrade " + gameName);
            play_game_btn.icon = "system-software-update.png";
        }

        read_author_desc_btn.subtext = qsTr(gameDescription);
        previewImages.model = screenshotUrls;
        gameIndex = index;
        mainview.statepoint = "details";
    }

    SystemPalette {
        id: activePalette;
    }

    Image {
        id: backIcon;
        source: "icons/go-previous.png";
        // z: 100;
        anchors {
            // bottom: previewImages.top;
            margins: 10;
        }

        MouseArea {
            id: backIconMouseArea;
            anchors.fill: parent;
            hoverEnabled: true;
            onClicked: {
               mainview.statepoint = "mainwindow";
           }
        }
    }

    Component {
        id: gameScreenshotsDelegate;
        Image {
            height: GridView.view.height;
            width: GridView.view.width;
            source: modelData
        }
    }

   GridView {
        id: previewImages
        width: parent.width / 3;
        height: parent.height * 1 / 5 - 10;
        delegate: gameScreenshotsDelegate;
        anchors {
            top: backIcon.bottom;
        }
   }

    Button {
        id: play_game_btn;
        height: parent.height * 1 / 5 - 10;
        icon: "icons/media-playback-start.png";
        text: qsTr("Play the game");
        subtext: qsTr("1697 others currently playing");
        anchors {
            left: previewImages.right;
            right: parent.right;
            top: parent.top;
            margins: 5;
        }

        onClicked: {
            gameWindowManager.setProject(gameIndex);
        }
    }

    Button {
        id: read_author_desc_btn;
        width: play_game_btn.width / 2;
        icon: "icons/dialog-information.png";
        text: qsTr("Read Author's Description");
        subtext: qsTr("No description");
        anchors {
            top: play_game_btn.bottom;
            left: previewImages.right;
            right: parent.right;
            margins: 5;
        }

        onClicked: {
            console.log("this doesn't do anything yet...");
        }
    }

    Button {
        id: high_scores_btn;
        width: play_game_btn.width / 2;
        icon: "icons/games-highscores.png";
        text: qsTr("High Scores");
        subtext: "Your global high-score: 258th";
        anchors {
            top: read_author_desc_btn.bottom;
            left: previewImages.right;
            margins: 5;
        }

        onClicked: {
            console.log("this doesn't do anything yet...");
        }
    }

    Button {
        id: achievements_btn;
        width: play_game_btn.width / 2;
        icon: "icons/games-achievements.png";
        text: qsTr("Achievements");
        subtext: "You have 4 of 16";
        anchors {
            top: read_author_desc_btn.bottom;
            left: high_scores_btn.right;
            right: parent.right;
            margins: 5;
        }

        onClicked: {
            console.log("this doesn't do anything yet...");
        }
    }

    Button {
        id: rate_comments_btn;
        width: play_game_btn.width / 2;
        icon: "icons/help-feedback.png";
        text: qsTr("Rate & Comment");
        subtext: "20984 ratings, 413 comments";
        anchors {
            top: high_scores_btn.bottom;
            left: previewImages.right;
            margins: 5;
        }

        onClicked: {
            gameWindowManager.buildCommentsModel(gameIndex);
            mainview.statepoint = "comments";
        }
    }

    Button {
        id: donate_btn;
        width: play_game_btn.width / 2;
        icon: "icons/help-donate.png";
        text: qsTr("Donate");
        subtext: "€3 suggested";
        anchors {
            top: achievements_btn.bottom;
            left: rate_comments_btn.right;
            right: parent.right;
            margins: 5;
        }

        onClicked: {
            console.log("this doesn't do anything yet...");
        }
    }

    Text {
        id: new_comments;
        text: qsTr("New Comments");
        color: "white";
        font.pixelSize: 20;
        anchors {
            top: rate_comments_btn.bottom;
            left: previewImages.right;
            margins: 5;
        }
    }
}
