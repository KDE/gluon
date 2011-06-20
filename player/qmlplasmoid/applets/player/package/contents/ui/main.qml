/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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
import org.kde.plasma.graphicswidgets 0.1 as PlasmaWidgets
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.graphicslayouts 4.7 as GraphicsLayouts
import org.gamingfreedom.gluon.gluonplayerimports 0.1 as GluonPlayer

Item {
    width: 300
    height: 300

    GluonPlayer.GluonPlayerAdapter { id: gluonPlayerAdapter }

    function dlProgress(bytesReceived, bytesTotal) {
            console.log("DOWNLOAD " + bytesReceived + " OF " + bytesTotal);
    }

    Component {
        id: gameItemsDelegate

        Item {
            anchors.margins: 10
            width: ListView.view.width
            height: 50

            PlasmaWidgets.IconWidget {
                anchors.left: parent.left; anchors.top: parent.top; anchors.bottom: parent.bottom;
                anchors.right: actionButton.left
                text: GameName
                orientation: Qt.Horizontal

                Component.onCompleted: {
                    setIcon("gluon-player")
                }
            }

            PlasmaWidgets.IconWidget {
                id: actionButton
                anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.right: parent.right;

                Component.onCompleted: {
                    if (Status == GluonPlayer.GameItem.Installed) {
                        setIcon("media-playback-start");
                    } else {
                        setIcon("download");
                    }
                }

                onClicked: {
                    if (Status == GluonPlayer.GameItem.Installed) {
                        console.log("Playing not yet implemented");
                    } else {
                        gluonPlayerAdapter.ocsProvider.downloadGame(Id);
                    }
                }
            }
        }
    }

    ListView {
        anchors.fill: parent
        spacing: 5

        model: GluonPlayer.AllGameItemsModel { }
        delegate: gameItemsDelegate
    }
}

