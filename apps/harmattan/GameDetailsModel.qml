/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

VisualItemModel {

    id: gameDetailsModel

    ListItem {
        iconSource: "media-playback-start.png";
        titleText: "Play " + mainPage.selectedProjectName;
        subtitleText: "1697 others currently playing";
        drillDownArrow: true;
        mousePressed: playListItemMouseArea.pressed;

        MouseArea {
            id: playListItemMouseArea;
            anchors.fill: parent;
            onClicked: {
                gameWindowManager.setProject(mainPage.selectedItem);
            }
        }
    }

    ListItem {
        iconSource: "dialog-information.png";
        titleText: "Read Author's Description";
        subtitleText: mainPage.selectedProjectDescription;
        drillDownArrow: true;
        mousePressed: descriptionListItemMouseArea.pressed;

        MouseArea {
            id: descriptionListItemMouseArea;
            anchors.fill: parent;
            onClicked: {
            }
        }
    }

    ListItem {
        iconSource: "ksnapshot.png";
        titleText: "Screenshots";
        subtitleText: "Check out the screenshots";
        drillDownArrow: true;
        mousePressed : screenshotListItemMouseArea.pressed;

        MouseArea {
            id: screenshotListItemMouseArea;
            anchors.fill: parent;
            onClicked: {
            }
        }
    }

    ListItem {
        iconSource: "games-achievements.png";
        titleText: "Achievements";
        subtitleText: "You have 4 of 16";
        drillDownArrow: true;
        mousePressed: achievementsScoresListItemMouseArea.pressed;

        MouseArea {
            id: achievementsScoresListItemMouseArea;
            anchors.fill: parent;
            onClicked: {
            }
        }
    }

    ListItem {
        iconSource: "games-highscores.png";
        titleText: "High Scores";
        subtitleText: "Your global high-score: 258th";
        drillDownArrow: true;
        mousePressed: highScoresListItemMouseArea.pressed;

        MouseArea {
            id: highScoresListItemMouseArea;
            anchors.fill: parent;
            onClicked: {
            }
        }
    }

    ListItem {
        iconSource: "help-feedback.png";
        titleText: "Rate & Comment";
        subtitleText: "20984 ratings, 413 comments";
        drillDownArrow: true;
        mousePressed: rateCommentScoresListItemMouseArea.pressed;

        MouseArea {
            id: rateCommentScoresListItemMouseArea;
            anchors.fill: parent;
            onClicked: {
            }
        }
    }

    ListItem {
        iconSource: "help-donate.png";
        titleText: "Donate";
        subtitleText: "€3 suggested";
        drillDownArrow: true;
        mousePressed: donateScoresListItemMouseArea.pressed;

        MouseArea {
            id: donateScoresListItemMouseArea;
            anchors.fill: parent;
            onClicked: {
            }
        }
    }
}
