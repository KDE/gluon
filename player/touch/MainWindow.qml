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

    color: "black";
    anchors.fill: parent;

   function login() {
       console.log("Provider have been already initialized!");
       authentication.login(lgn.username, lgn.password);
       mainview.statepoint = "home";
   }

   Image {
       id: gluon_logo;
       source: "icons/hi256-app-gluon.png";
       width: parent.width/2 * 4/5;
       height: parent.height * 3/5;
       fillMode: Image.PreserveAspectFit;
       anchors {
           horizontalCenter: parent.horizontalCenter;
           horizontalCenterOffset: -parent.width/4;
           verticalCenter: parent.verticalCenter;
           margins: 10;
       }
   }

    Login {
        id: lgn;
        objectName: qsTr("login");
        width: parent.width / 2;
        height: parent.height * 2 / 5 - 10;
        anchors {
            left: gluon_logo.right;
            right: parent.right;
            top: parent.top;
            margins: 10;
        }
    }

    Button {
        id: new_user;
        width: parent.width / 4 - 5;
        height: parent.height * 1 / 5 - 10;
        icon: "icons/list-add-user.png";
        text: qsTr("New User");
        anchors {
            top: lgn.bottom;
            left: gluon_logo.right;
            margins: 10;
        }

        onClicked: {
            mainview.statepoint = "registration";
        }
    }

    Button {
        id: log_on;
        width: parent.width / 4 - 5;
        height: parent.height * 1 / 5 - 10;
        icon: "icons/im-user.png";
        text: qsTr("Log On");
        anchors {
            top: lgn.bottom;
            left: new_user.right;
            right: parent.right;
            margins: 10;
        }

        onClicked: {
            if (lgn.providerInitialized) {
                console.log("Provider have been already initialized!");
                authentication.login(lgn.username, lgn.password);
                mainview.statepoint = "home";
                mainview.loggedIn = true;
            } else {
                console.log("Provider is not initialized yet!");
            }
        }
    }

    Button {
        id: forgotten_details;
        width: parent.width / 2;
        height: parent.height * 1 / 5 - 10;
        icon: "icons/help-hint.png";
        text: qsTr("Forgotten Your Details?");
        subtext: qsTr("Send new password to your email address");
        anchors {
            top: log_on.bottom;
            left: gluon_logo.right;
            right: parent.right;
            margins: 10;
        }

        onClicked: {
            mainview.statepoint = "mainwindow";
            Qt.openUrlExternally("http://opendesktop.org/usermanager/mailpass.php");
        }
    }

    Button {
        id: play;
        width: parent.width / 2;
        height: parent.height * 1 / 5 - 10;
        icon: "icons/media-playback-start.png";
        text: qsTr("Play Without Logging On");
        subtext: gameWindowManager.availableGamesCount() + " games available";
        anchors {
            top: forgotten_details.bottom;
            left: gluon_logo.right;
            bottom: parent.bottom;
            right: parent.right;
            margins: 10;
        }

        onClicked: {
            mainview.statepoint = "home";
        }
    }

    Keys.onReturnPressed: login();
    Keys.onEnterPressed: login();
}
