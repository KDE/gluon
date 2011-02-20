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
    id: gluon_player;

    color: "black";
    anchors.fill: parent;

    SystemPalette {
        id: activePalette;
    }

    Component {
        id: commentItemsDelegate;
        Button {
            id: commentItem;
            width: ListView.view.width;
            icon: "icons/hi32-app-gluon.png";
            text: qsTr(author + " " + title + " " + dateTime + " " + rating);
            subtext: qsTr(body);
        }
    }

    ListView {
        width: 200;
        height: 250;
        anchors.fill: parent;
        model: commentItemsModel;
        delegate: commentItemsDelegate;
        spacing: 5;

        header: Button {
            id: comment;
            icon: "icons/user-group-new.png";
            text: "gamerdude";
            onClicked: console.log("this doesn't do anything yet...");
        }
    }


}
