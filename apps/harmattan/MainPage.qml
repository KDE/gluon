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
import com.nokia.meego 1.0
import com.nokia.extras 1.0

Page {
    id: mainPage;

    property int selectedItem: 0;
    property string selectedProjectName;
    property string selectedProjectDescription;

    function pushPage(file) {
        var component = Qt.createComponent(file)
        if (component.status == Component.Ready)
            pageStack.push(component);
        else
            console.log("Error loading component:", component.errorString());
    }

    Component {
        id: gameItemsDelegate;

        ListItem {
            iconSource: "hi32-app-gluon.png";
            titleText: qsTr(projectName);
            subtitleText: qsTr(projectDescription);
            drillDownArrow: true;
            mousePressed: listItemMouseArea.pressed;

            MouseArea {
                id: listItemMouseArea;
                anchors.fill: parent;
                onClicked: {
                    mainPage.selectedItem = index;
                    mainPage.selectedProjectName = projectName;
                    mainPage.selectedProjectDescription = projectDescription;
                    pageStack.push("qrc:/GameDetailsPage.qml");
               }
            }
        }
    }

    ListView {
        id: gameItemsListView;

        anchors.fill: parent;
        model: gameItemsModel;

        delegate: gameItemsDelegate;

        header:
                ListItem {
                    iconSource: "get-hot-new-stuff.png";
                    titleText: qsTr("Get More Games");
                    subtitleText: gameItemsModel.downloadableCount + qsTr(" new games, ") + gameItemsModel.upgradableCount + qsTr(" updated");
                    drillDownArrow: true;
                    mousePressed: headerMouseArea.pressed;

                    MouseArea {
                        id: headerMouseArea;
                        anchors.fill: parent;
                        onClicked: {
                          // gameItemsDelegate.clicked();
                        }
                    }
                }
    }

    ScrollDecorator {
        flickableItem: gameItemsListView
    }
}
