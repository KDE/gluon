/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2013 Arjen Hiemstra <ahiemstra@heimr.nl>
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

import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.1

Item {
    id: base;

    SystemPalette { id: palette }

    property int gridWidth: _gridWidth;
    property int gridHeight: _gridHeight;

    Column {
        width: 60 * base.gridWidth

        Rectangle {
            width: parent.width;
            height: 6 * base.gridHeight;
            color: palette.alternateBase;

            Row {
                width: childrenRect.width;
                height: 5 * base.gridHeight;
                anchors.centerIn: parent;
                spacing: base.gridWidth;

                Image {
                    anchors.verticalCenter: parent.verticalCenter;
                    source: creatorIcon;
                    width: 5 * base.gridHeight;
                    height: width;
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter;
                    text: "Welcome to Gluon Creator"
                    font.pixelSize: 3 * base.gridHeight;
                }
            }

            Button {
                anchors {
                    top: parent.top;
                    topMargin: 0.5 * base.gridHeight;
                    right: parent.right;
                    rightMargin: 0.5 * base.gridWidth;
                }

                width: base.gridWidth;
                height: width;

                iconName: "window-close";

                onClicked: mainWindow.closeWelcomeDialog();
            }
        }

        Rectangle {
            width: parent.width;
            height: 1;
            color: palette.dark;
        }

        Item {
            width: parent.width - base.gridWidth;
            height: 30 * base.gridHeight;
            anchors.horizontalCenter: parent.horizontalCenter;

            WelcomeDialogColumn {
                id: newItemsColumn;

                height: parent.height;
                width: parent.width / 3 - 1;

                gridHeight: base.gridHeight;
                gridWidth: base.gridWidth;

                headerText: "Create";
                headerVisible: rightSide.depth == 1;

                model: newItemsModel;

                onItemClicked: {
                    if( rightSide.depth == 1 ) {
                        rightSide.push( newProjectPage );
                    } else {
                        rightSide.replace( newProjectPage );
                    }
                }
            }

            StackView {
                id: rightSide;
                clip: true;

                anchors.right: parent.right;
                height: parent.height;
                width: parent.width - newItemsColumn.width - 1;

                initialItem:
                Item {
                    anchors.fill: parent;

                    WelcomeDialogColumn {
                        height: parent.height;
                        width: parent.width / 2 - 1;

                        gridHeight: base.gridHeight;
                        gridWidth: base.gridWidth;

                        model: recentFiles;

                        headerText: "Open";

                        listHeader: openColumnHeader;

                        onItemClicked: mainWindow.openRecentProject( index );
                    }

                    WelcomeDialogColumn {
                        anchors.right: parent.right;
                        height: parent.height;
                        width: parent.width / 2 - 1;

                        gridHeight: base.gridHeight;
                        gridWidth: base.gridWidth;

                        model: newsItemsModel;

                        headerText: "News";
                    }
                }
            }
        }

        Rectangle {
            width: parent.width;
            height: 1;
            color: palette.dark;
        }

        Rectangle {
            width: parent.width;
            height: 4 * base.gridHeight;
            color: palette.alternateBase;

            Row {
                anchors.fill: parent;
                ToolButton {
                    width: parent.width / 3;
                    height: parent.height;
                    text: "New to Creator? Click here!";

                    onClicked: { dialog.allowClose = true; dialog.close(); showIntroductionTimer.start(); }
                }

                ToolButton {
                    width: parent.width / 3;
                    height: parent.height;
                    text: "Visit gamingfreedom.org";

                    onClicked: Qt.openUrlExternally( "http://www.gamingfreedom.org" );
                }

                ToolButton {
                    width: parent.width / 3;
                    height: parent.height;
                    text: "Not logged in.";
                }
            }
        }
    }

    ListModel {
        id: newItemsModel;

        ListElement { data: "Empty Project"; }
    }

    ListModel {
        id: newsItemsModel;

        ListElement { data: "Some news"; }
        ListElement { data: "Some news"; }
        ListElement { data: "Some news"; }
    }

    Component {
        id: newProjectPage;

        NewProjectDialogPage { }
    }

    Component {
        id: openColumnHeader;

        ToolButton {
            width: parent.width;
            height: 3 * base.gridHeight;

            text: "Open project..."

            onClicked: mainWindow.showOpenProjectDialog();
        }
    }
}
