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

Rectangle {

    color: "black";
    anchors.fill: parent;

    property int gameIndex;

    function propagate(gameName, gameDescription, index) {
        play_game_btn.text = qsTr("Play " + gameName);
        read_author_desc_btn.subtext = qsTr(gameDescription);
        gameIndex = index;
        mainview.statepoint = "details";
    }

    SystemPalette {
        id: activePalette;
    }

   Image {
       id: game_main_img;
       source: "icons/hi256-app-gluon.png";
       width: parent.width/2 * 4/5;
       height: parent.height * 3/5;
       fillMode: Image.PreserveAspectFit;
       anchors {
           horizontalCenter: parent.horizontalCenter;
           horizontalCenterOffset: -parent.width/4;
           verticalCenter: parent.verticalCenter;
           margins: 10;
       }
   }

    Button {
        id: play_game_btn;
        width: parent.width / 2;
        height: parent.height * 1 / 5 - 10;
        icon: "icons/media-playback-start.png";
        text: qsTr("Play the game");
        subtext: qsTr("1697 others currently playing");
        anchors {
            left: game_main_img.right;
            right: parent.right;
            top: parent.top;
            margins: 10;
        }

        onClicked: {
            gameWindowManager.setProject(gameIndex);
        }
    }

    Button {
        id: read_author_desc_btn;
        width: parent.width / 2;
        height: parent.height * 1 / 5;
        icon: "icons/im-user.png";
        text: qsTr("Read Author's Description");
        subtext: qsTr("No description");
        anchors {
            top: play_game_btn.bottom;
            left: game_main_img.right;
            right: parent.right;
            margins: 10;
        }

        onClicked: console.log("this doesn't do anything yet...");
    }

    Button {
        id: high_scores_btn;
        width: parent.width / 4;
        height: parent.height * 1 / 5;
        icon: "icons/help-hint.png";
        text: qsTr("High Scores");
        subtext: "Your global high-score: 258th";
        anchors {
            top: read_author_desc_btn.bottom;
            left: game_main_img.right;
            margins: 10;
        }

        onClicked: console.log("this doesn't do anything yet...");
    }

    Button {
        id: achievements_btn;
        width: parent.width / 4;
        height: parent.height * 1 / 5;
        icon: "icons/media-playback-start.png";
        text: qsTr("Achievements");
        subtext: "You have 4 of 16";
        anchors {
            top: read_author_desc_btn.bottom;
            left: high_scores_btn.right;
            right: parent.right;
            margins: 10;
        }

        onClicked: console.log("this doesn't do anything yet...");
    }

    Button {
        id: rate_comments_btn;
        width: parent.width / 4;
        height: parent.height * 1 / 5;
        icon: "icons/media-playback-start.png";
        text: qsTr("Rate & Comment");
        subtext: "20984 ratings, 413 comments";
        anchors {
            top: high_scores_btn.bottom;
            left: game_main_img.right;
            margins: 10;
        }

        onClicked: {
            gameWindowManager.buildCommentsModel(gameIndex);
            mainview.statepoint = "comments";
        }
    }

    Button {
        id: donate_btn;
        width: parent.width / 4;
        height: parent.height * 1 / 5;
        icon: "icons/media-playback-start.png";
        text: qsTr("Donate");
        subtext: qsTr("€3 suggested");
        anchors {
            top: achievements_btn.bottom;
            left: rate_comments_btn.right;
            right: parent.right;
            margins: 10;
        }

        onClicked: console.log("this doesn't do anything yet...");
    }

    Text {
        id: new_comments;
        text: qsTr("New Comments");
        anchors {
            top: rate_comments_btn.bottom;
        }
    }
}
