/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Shreya Pandit <shreya@shreyapandit.com>
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
import org.kde.plasma.extras 0.1 as PlasmaExtras
import org.kde.plasma.components 0.1 as PlasmaComponents
import Gluon.Creator.Introduction 1.0

Item {
    id: base;

    Rectangle {
        id: topOverlay;

        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: viewport.top;
        opacity: 0.7;
        color: "black";
    }

    Rectangle {

        id: leftOverlay;
        anchors.top: topOverlay.bottom;
        anchors.left: parent.left;
        anchors.right: viewport.left;
        anchors.bottom: bottomOverlay.top;
        opacity: 0.7;
        color: "black";
     }

    Rectangle {
        id: rightOverlay;

        anchors.top: topOverlay.bottom;
        anchors.left: viewport.right;
        anchors.right: parent.right;
        anchors.bottom: bottomOverlay.top;

        opacity: 0.7;
        color: "black";
    }

    Rectangle {
        id: bottomOverlay;

        anchors.top: viewport.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;

        opacity: 0.7;
        color: "black";
    }


    Item {
        id: viewport;

        x: overlay.x;
        y: overlay.y;
        width: overlay.width;
        height: overlay.height;

        Behavior on width { NumberAnimation { duration: 500; } }
        Behavior on height { NumberAnimation { duration: 500; } }
        Behavior on x { NumberAnimation { duration: 500; } }
        Behavior on y { NumberAnimation { duration: 500; } }

        MouseArea {
            anchors.fill: parent;

            onClicked: d.incrementCurrentDockerIndex();
        }
    }

    PlasmaCore.FrameSvgItem {
        id: textFrame;

        anchors.centerIn: parent
        width: parent.width / 4;
        height: parent.height / 4;

        imagePath: "translucent/dialogs/background"

        PlasmaExtras.Paragraph {
            anchors.fill: parent;
            anchors.margins: 10;
            text: textData.text( d.currentDockerIndex != -1 ? d.dockerNames[ d.currentDockerIndex ] : "" );
        }

        PlasmaComponents.Button {
            anchors {
                bottom: parent.bottom;
                bottomMargin: 10;
                left: parent.left;
                leftMargin: 10;
            }

            text: d.currentDockerIndex != d.dockerNames.length - 1 ? "Previous" : "Restart";
            opacity: d.currentDockerIndex > 0;
            Behavior on opacity { NumberAnimation { } }

            onClicked: d.currentDockerIndex == d.dockerNames.length - 1 ? d.currentDockerIndex = 1 : d.currentDockerIndex--;
        }

        PlasmaComponents.Button {
            anchors {
                bottom: parent.bottom;
                bottomMargin: 10;
                right: parent.right;
                rightMargin: 10;
            }

            text: d.currentDockerIndex != d.dockerNames.length - 1 ? "Next" : "Quit";

            onClicked: d.currentDockerIndex == d.dockerNames.length - 1 ? mainWindow.closeQmlOverlay() : d.currentDockerIndex++;
        }
    }

    DockerOverlay {
        id: overlay;

        x: parent.width / 2;
        y: parent.height / 2;
        width: 0;
        height: 0;

        dockerName: d.currentDockerIndex != -1 ? d.dockerNames[ d.currentDockerIndex ] : "";
    }

    IntroductionText {
        id: textData;
    }

    QtObject {
        id: d;

        property variant dockerNames: [ "Start", "ComponentsDock", "ProjectDock", "MessageDock", "SceneDock", "PropertiesDock", "End" ];
        property int currentDockerIndex: 0;
    }
}
