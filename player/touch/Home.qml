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

import QtQuick 1.0

Rectangle {

    property bool moreGames: false;

    color: "black";
    anchors.fill: parent;

    Component {
        id: gameItemsDelegate;
        Button {
            id: gameItem;
            width: ListView.view.width;
            icon: "icons/hi32-app-gluon.png";
            text: qsTr(projectName);
            subtext: qsTr(projectDescription);

            onClicked: {
                detailsPage.propagate(projectName, projectDescription, screenshotUrls, status, index);
            }
        }
    }

    Component {
        id: gameItemsDelegateMoreGames;
        Button {
            id: gameItemMoreGames;
            width: ListView.view.width;
            icon: "icons/hi32-app-gluon.png";
            text: qsTr(projectNameDownloadable);
            subtext: qsTr(projectDescriptionDownloadable);

            onClicked: {
                detailsPage.propagate(projectNameDownloadable, projectDescriptionDownloadable, screenshotUrlsDownloadable, statusDownloadable, index);
            }
        }
    }

    ListView {
        id: gameItemsListView;

        width: 200;
        height: 250;
        anchors.fill: parent;
        model: gameItemsModel;
        delegate: gameItemsDelegate;
        spacing: 5;

        header:
            Rectangle {
                color: homePage.color;
                width: ListView.view.width;
                height: listViewHeaderButton.height + 5;
                Button {
                    id: listViewHeaderButton;
                    icon: "icons/get-hot-new-stuff.png";
                    text: qsTr("Get More Games");
                    subtext: gameItemsModel.downloadableCount + qsTr(" new games, ") + gameItemsModel.upgradableCount + qsTr(" updated");

                    onClicked: {
                        if (!mainview.loggedIn) {
                            mainview.statepoint = "mainwindow";
                        } else {
                            if (!moreGames) {
                                text = qsTr("Back to the downloaded games");
                                gameItemsListView.delegate = gameItemsDelegateMoreGames;
                                moreGames = true;
                            } else {
                                text = qsTr("Get More Games");
                                gameItemsListView.delegate = gameItemsDelegate;
                                moreGames = false;
                            }
                        }
                    }
                }
            }
    }
}
