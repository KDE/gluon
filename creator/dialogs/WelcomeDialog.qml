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

import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.extras 0.1 as PlasmaExtras
import org.kde.qtextracomponents 0.1

Item {
    id: base;

    Rectangle {
        id: overlayBackground;

        anchors.fill: parent;
        color: "black";
        opacity: 0;

        Behavior on opacity { NumberAnimation { duration: 250; } }
    }

    PlasmaComponents.Dialog {
        id: dialog;

        title: PlasmaCore.FrameSvgItem {
            width: 800;
            height: 75;

            imagePath: "widgets/extender-dragger";
            prefix: "root";

            QIconItem { id: icon; width: 64; height: 64; icon: "gluon_creator"; }
            PlasmaExtras.Title {
                anchors.centerIn: parent;
                text: "Welcome to Gluon Creator"
            }

            PlasmaComponents.ToolButton {
                anchors {
                    top: parent.top;
                    right: parent.right;
                }
                iconSource: "window-close";

                onClicked: { dialog.allowClose = true; dialog.close(); overlayBackground.opacity = 0; closeOverlayTimer.start(); }
            }
        }

        content:
        Item {
            width: 800;
            height: 430;

            WelcomeDialogColumn {
                id: newItemsColumn;

                height: parent.height;
                width: parent.width / 3 - 1;

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

            PlasmaComponents.PageStack {
                id: rightSide;
                clip: true;

                anchors.right: parent.right;
                height: parent.height;
                width: parent.width - newItemsColumn.width - 1;

                initialPage:
                PlasmaComponents.Page {
                    WelcomeDialogColumn {
                        height: parent.height;
                        width: parent.width / 2 - 1;

                        model: recentFiles;

                        headerText: "Open";

                        listHeader: openColumnHeader;

                        onItemClicked: mainWindow.openRecentProject( index );
                    }

                    WelcomeDialogColumn {
                        anchors.right: parent.right;
                        height: parent.height;
                        width: parent.width / 2 - 1;

                        model: newsItemsModel;

                        headerText: "News";
                    }
                }
            }
        }

        buttons:
        PlasmaCore.FrameSvgItem {
            width: parent.width;
            height: 45;

            imagePath: "widgets/extender-dragger";
            prefix: "root";

            rotation: 180;

            Row {
                anchors.fill: parent;
                anchors.bottomMargin: 10;

                rotation: 180;

                PlasmaComponents.ToolButton {
                    width: parent.width / 3;
                    height: parent.height;
                    flat: true;
                    text: "New to Creator? Click here!";

                    onClicked: { dialog.allowClose = true; dialog.close(); showIntroductionTimer.start(); }
                }

                PlasmaComponents.ToolButton {
                    width: parent.width / 3;
                    height: parent.height;
                    flat: true;
                    text: "Visit gamingfreedom.org";

                    onClicked: Qt.openUrlExternally( "http://www.gamingfreedom.org" );
                }

                PlasmaComponents.ToolButton {
                    width: parent.width / 3;
                    height: parent.height;
                    flat: true;
                    text: "Not logged in.";
                }
            }
        }

        //Hack because clicking outside the dialog will always close it without us being able to prevent that
        property bool allowClose: false;
        onStatusChanged: if( status == PlasmaComponents.DialogStatus.Closing && !allowClose ) dialog.open();
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

        Item {
            width: parent.width;
            height: 50;

            PlasmaComponents.Highlight {
                id: headerHighlight;
                anchors.fill: parent;
                opacity: 0;
                Behavior on opacity { NumberAnimation { } }
            }

            PlasmaComponents.Label {
                anchors {
                    left: parent.left;
                    leftMargin: 10;
                    verticalCenter: parent.verticalCenter;
                }
                text: "Open project..."
            }

            MouseArea {
                anchors.fill: parent;
                hoverEnabled: true;
                onEntered: headerHighlight.opacity = 1;
                onExited: headerHighlight.opacity = 0;
                onClicked: mainWindow.showOpenProjectDialog();
            }
        }
    }

    Component.onCompleted: overlayBackground.opacity = 0.7; //So we fade in the background instead of it immediately flashing into view

    // Because dialog.open() cannot be called from Compnent.onCompleted apparently...
    Timer {
        interval: 500;
        running: true;
        onTriggered: dialog.open();
    }

    //Workaround for a bug in Dialog where status will never become Closed
    Timer {
        id: showIntroductionTimer;
        interval: 250;
        onTriggered: mainWindow.showIntroduction();
    }

    Timer {
        id: closeOverlayTimer;
        interval: 250;
        onTriggered: mainWindow.closeQmlOverlay();
    }
}
