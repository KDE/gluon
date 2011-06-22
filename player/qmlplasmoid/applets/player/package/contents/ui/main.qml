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
    id: rootItem
    width: 300
    height: 300
    //clip: true

    GluonPlayer.GluonPlayerAdapter { id: gluonPlayerAdapter }

    function dlProgress(bytesReceived, bytesTotal) {
            progressBar.width = bytesReceived*rootItem.width/bytesTotal;
    }

    GameDetails {
        id: gameDetails
        width: rootItem.width; height: rootItem.height
        anchors.left: rootItem.right;
    }

    HomeScreen {
        id: homeScreen

        width: rootItem.width; height: rootItem.height
    }

    transitions: Transition {
         // smoothly reanchor myRect and move into new position
         AnchorAnimation { duration: 200 }
     }

    states : [
        State {
            name: "showGameDetails"
            AnchorChanges {
                target: gameDetails
                anchors.left: rootItem.left
            }
            AnchorChanges {
                target: homeScreen
                anchors.right: rootItem.left
            }
        }
    ]
}
