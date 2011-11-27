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

        ListItem {
            iconSource: "icons/hi32-app-gluon.png";
            titleText: qsTr(projectName);
            subtitleText: qsTr(projectDescription);
            drillDownArrow: true;
        }
    }

    ListView {
        id: gameItemsListView;

        anchors.fill: parent;
        model: gameItemsModel;
        delegate: gameItemsDelegate;
        spacing: 5;

        header:
            ListItem {
                iconSource: "icons/get-hot-new-stuff.png";
                titleText: qsTr("Get More Games");
                subtitleText: gameItemsModel.downloadableCount + qsTr(" new games, ") + gameItemsModel.upgradableCount + qsTr(" updated");
                drillDownArrow: true;
            }
    }

    ScrollDecorator {
        flickableItem: gameItemsListView
    }
}
