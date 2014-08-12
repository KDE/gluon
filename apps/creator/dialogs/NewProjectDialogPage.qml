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

import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: base;

    Item {
        anchors.fill: parent;

        Column {
            anchors.fill: parent;
            anchors.margins: 10;
            spacing: 5;

            Label {
                width: parent.width;
                text: "Create Empty Project";
                horizontalAlignment: Text.AlignHCenter;

            }
            Label {
                text: "Project Name";
            }
            TextField {
                id: projectNameField;
                width: parent.width;
            }
            Label {
                text: "Location";
            }
            Row {
                width: parent.width;

                TextField {
                    id: locationField;
                    width: parent.width - selectDirIcon.width;
                }

                Button {
                    id: selectDirIcon;
                    iconSource: "folder-open";
                    onClicked: locationField.text = mainWindow.selectDirectory();
                }
            }
            Label {
                id: projectNameErrorText;

                text: "Project name cannot be empty.";
                color: "red";

                opacity: projectNameField.text == "";
                Behavior on opacity { NumberAnimation { } }
            }

            Label {
                id: locationErrorText;

                text: "Location cannot be empty.";
                color: "red";

                opacity: locationField.text == "";
                Behavior on opacity { NumberAnimation { } }
            }
        }

        Button {
            anchors {
                bottom: parent.bottom;
                bottomMargin: 5;
                right: parent.horizontalCenter;
                rightMargin: 10;
            }
            text: "Ok";

            onClicked: {
                if( projectNameField.text === "" || locationField.text === "" )
                    return;

                mainWindow.createProject( projectNameField.text, locationField.text );
            }
        }

        Button {
            anchors {
                bottom: parent.bottom;
                bottomMargin: 5;
                left: parent.horizontalCenter;
                leftMargin: 10;
            }
            text: "Cancel";

            onClicked: base.Stack.view.pop();
        }
    }
}
