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
import com.nokia.meego 1.1
import com.nokia.extras 1.1

Page {

    property bool moreGames: false;

    anchors.fill: parent;

    ListDelegate {
        id: gameItemsDelegate;
        Image {
            source: "image://theme/icon-m-common-drilldown-arrow" + (theme.inverted ? "-inverse" : "");
            anchors.right: parent.right;
            anchors.verticalCenter: parent.verticalCenter;
        }
        onClicked: {  }
    }

    ListDelegate {
        id: gameItemsDelegateMoreGames;
        Image {
            source: "image://theme/icon-m-common-drilldown-arrow" + (theme.inverted ? "-inverse" : "");
            anchors.right: parent.right;
            anchors.verticalCenter: parent.verticalCenter;
        }
        onClicked: {  }
    }

    ListView {
        id: gameItemsListView;

        anchors.fill: parent;
        model: gameItemsModel;
        delegate: gameItemsDelegate;
        spacing: 5;

        header:
            Rectangle {
                width: ListView.view.width;
                height: listViewHeaderButton.height + 5;
                Button {
                    id: listViewHeaderButton;
                    iconSource: "icons/get-hot-new-stuff.png";
                    text: qsTr("Get More Games");
                    // subtext: gameItemsModel.downloadableCount + qsTr(" new games, ") + gameItemsModel.upgradableCount + qsTr(" updated");

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
    ScrollDecorator {
        flickableItem: gameItemsListView
    }
}
