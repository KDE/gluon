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
        iconSource: "icons/hi32-app-gluon.png";
        titleText: "Screenshots";
        subtitleText: "Check out the screenshots";
        drillDownArrow: true;
    }

    ListItem {
        iconSource: "icons/media-playback-start.png";
        titleText: "Play " + mainPage.selectedProjectName;
        subtitleText: "1697 others currently playing";
        drillDownArrow: true;

        MouseArea {
            id: playListItemMuseArea;
            anchors.fill: parent;
            onClicked: {
                gameWindowManager.setProject(mainPage.selectedItem);
            }
        }
    }

    ListItem {
        iconSource: "icons/dialog-information.png";
        titleText: "Read Author's Description";
        subtitleText: mainPage.selectedProjectDescription;
        drillDownArrow: true;
    }

    ListItem {
        iconSource: "icons/games-highscores.png";
        titleText: "High Scores";
        subtitleText: "Your global high-score: 258th";
        drillDownArrow: true;
    }

    ListItem {
        iconSource: "icons/games-achievements.png";
        titleText: "Achievements";
        subtitleText: "You have 4 of 16";
        drillDownArrow: true;
    }

    ListItem {
        iconSource: "icons/help-feedback.png";
        titleText: "Rate & Comment";
        subtitleText: "20984 ratings, 413 comments";
        drillDownArrow: true;
    }

    ListItem {
        iconSource: "icons/help-donate.png";
        titleText: "Donate";
        subtitleText: "€3 suggested";
        drillDownArrow: true;
    }

    ListItem {
        iconSource: "icons/hi32-app-gluon.png";
        titleText: "Comments";
        subtitleText: "Check out the comments";
        drillDownArrow: true;
    }
}
