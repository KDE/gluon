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

    Component {
        id: gameItemsDelegate;

        Item {
            BorderImage {
                id: background;
                // Fill page porders
                anchors {
                    fill: parent;
                    leftMargin: -16;
                    rightMargin: -16;
                }

                visible: mouseArea.pressed;
                source: theme.inverted ? "image://theme/meegotouch-panel-inverted-background-pressed" : "image://theme/meegotouch-panel-background-pressed";
            }

            Row {
                anchors.fill: parent;
                spacing: 16;

                Image {
                    anchors.verticalCenter: parent.verticalCenter;
                    visible: true;
                    width: 32;
                    height: 32;
                    source: "icons/hi32-app-gluon.png";
                }

                Column {
                    anchors.verticalCenter: parent.verticalCenter;

                    Label {
                        id: mainText
                        text: qsTr(projectName);
                        font.family: "Nokia Pure Text";
                        font.weight: Font.Bold;
                        font.pixelSize: 26;
                        color: mouseArea.pressed ? "#797979" : "#ffffff";
                    }

                    Label {
                        id: subText
                        text: qsTr(projectDescription);
                        font.family: "Nokia Pure Text Light";
                        font.weight: Font.Normal;
                        font.pixelSize: 22;
                        color: mouseArea.pressed ? "#797979" : "#C8C8C8";

                        visible: text != "";
                    }
                }
            }

            MouseArea {
                id: mouseArea;
                anchors.fill: parent;
                onClicked: {
                    gameItemsDelegate.clicked();
                }
            }

            Image {
                source: "image://theme/icon-m-common-drilldown-arrow" + (theme.inverted ? "-inverse" : "");
                anchors {
                    right: parent.right;
                    verticalCenter: parent.verticalCenter;
                }
            }

            // onClicked: {  }
        }
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
