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

Item {
    id: base;

    property alias headerText: headerTextItem.text;
    property bool headerVisible: true;

    property alias model: itemView.model;
    property string dataRole: "modelData";
    property alias listHeader: itemView.header;

    signal itemClicked( int index );

    Item {
        id: header;

        anchors {
            top: parent.top;
            left: parent.left;
            right: parent.right;
        }

        height: base.headerVisible ? 35 : 0;
        Behavior on height { NumberAnimation { } }

        clip: true;

        PlasmaExtras.Heading {
            id: headerTextItem;

            width: parent.width;
            text: "News";
            level: 2;
            horizontalAlignment: Text.AlignHCenter;
        }
    }

    PlasmaCore.FrameSvgItem {
        anchors {
            top: header.bottom;
            left: parent.left;
            right: parent.right;
            bottom: parent.bottom;
        }

        imagePath: "widgets/frame";
        prefix: "sunken";

        MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onEntered: itemView.highlightItem.opacity = 1;
            onPositionChanged: { var index = itemView.indexAt(mouse.x, mouse.y + itemView.contentY); if( index != -1 ) itemView.currentIndex = index }
            onExited: itemView.highlightItem.opacity = 0;
        }

        PlasmaExtras.ScrollArea {
            anchors.fill: parent;
            ListView {
                id: itemView;
                clip: true;

                delegate: listDelegate;
                highlight: listHighlight;
            }
        }
    }

    Component {
        id: listDelegate;

        Item {
            width: parent.width;
            height: 50;
            PlasmaComponents.Label {
                anchors {
                    left: parent.left;
                    leftMargin: 10;
                    right: parent.right;
                    rightMargin: 10;
                    verticalCenter: parent.verticalCenter;
                }
                elide: Text.ElideLeft;
                text: model[base.dataRole];
            }

            MouseArea {
                anchors.fill: parent;

                onClicked: base.itemClicked( index );
            }
        }
    }

    Component {
        id: listHighlight;

        PlasmaComponents.Highlight {
            opacity: 0;
            Behavior on opacity { NumberAnimation { } }
        }
    }
}
