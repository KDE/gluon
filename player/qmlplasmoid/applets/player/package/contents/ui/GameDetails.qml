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
    id: gameDetailsRootItem
    property string gameId
    property int buttonHeight

    Flickable {
        anchors.fill: parent
        contentWidth: gameDetailsColumn.width; contentHeight: gameDetailsColumn.height
        flickableDirection: Flickable.VerticalFlick

        Column {
            id: gameDetailsColumn
            anchors.fill: parent

            PlasmaWidgets.IconWidget {
                id: backButton
                height: gameDetailsRootItem.buttonHeight/2
                width: parent.width

                text: "Back"

                orientation: Qt.Horizontal
                icon:QIcon("go-previous")

                onClicked: {
                    rootItem.state = ""
                }
            }

            RatingWidget {
                height: 20; width: height*5;
                anchors.right: gameDetailsRootItem.right

                rating: 60
            }

            PlasmaWidgets.IconWidget {
                id: playButton
                height: gameDetailsRootItem.buttonHeight
                width: parent.width

                text: "Play"
                infoText: "Playing currently not supported"

                orientation: Qt.Horizontal
                icon:QIcon("media-playback-start")
            }

            PlasmaWidgets.IconWidget {
                id: descriptionButton
                height: gameDetailsRootItem.buttonHeight
                width: parent.width

                text: "Read author's description"

                orientation: Qt.Horizontal
                icon:QIcon("dialog-information")
            }

            PlasmaWidgets.IconWidget {
                id: highScoresButton
                height: gameDetailsRootItem.buttonHeight
                width: parent.width

                text: "Highscores"

                orientation: Qt.Horizontal
                icon:QIcon("games-highscores")
            }

            PlasmaWidgets.IconWidget {
                id: commentsButton
                height: gameDetailsRootItem.buttonHeight
                width: parent.width

                text: "Comments"

                orientation: Qt.Horizontal
                icon:QIcon("help-feedback")
            }

            PlasmaWidgets.IconWidget {
                id: donateButton
                height: gameDetailsRootItem.buttonHeight
                width: parent.width

                text: "Donate"

                orientation: Qt.Horizontal
                icon:QIcon("help-donate")
            }
        }
    }
}
