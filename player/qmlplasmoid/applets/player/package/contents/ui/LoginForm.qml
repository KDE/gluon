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
    Column {
        anchors.fill: parent
        spacing: 10

        Item {
            id: row1
            width: parent.width; height: 20

            PlasmaWidgets.BusyWidget {
                id: busyWidget
                width: parent.height; height: parent.height; anchors.top: parent.top; anchors.right: parent.right;
                visible: false

                running: false
            }

            PlasmaWidgets.IconWidget {
                id: loginStatusLabel
                anchors.fill: parent

                orientation: Qt.Horizontal
                text: "Not logged in"
            }
        }

        Item {
            id: row2
            width: parent.width; height: 20

            PlasmaWidgets.LineEdit {
                id: usernameEdit
                anchors.fill: parent
                clickMessage: "Username"
            }
        }

        Item {
            id: row3
            width: parent.width; height: 20

            PlasmaWidgets.LineEdit {
                id: passwordEdit
                anchors.fill: parent
                clickMessage: "Password"

                Component.onCompleted: nativeWidget.passwordMode = true;
            }
        }

        Item {
            id: row4
            width: parent.width; height: 20

            PlasmaWidgets.PushButton {
                id: loginButton
                anchors.fill: parent
                text: "Login"
                icon: QIcon("network-connect")

                onClicked: {
                    loginButton.enabled = false
                    busyWidget.running = true
                    loginStatusLabel.text = "Logging In"
                    busyWidget.visible = true
                    gluonPlayerAdapter.serviceProvider.login(usernameEdit.text, passwordEdit.text);
                    gluonPlayerAdapter.serviceProvider.loginFinished.connect(loggedIn)
                    gluonPlayerAdapter.serviceProvider.loginFailed.connect(loginFailed)
                }
            }
        }
    }

    Component.onCompleted: gluonPlayerAdapter.serviceProvider.providerInitialized.connect(init);

    function init()
    {
        usernameEdit.text = gluonPlayerAdapter.serviceProvider.username;
        passwordEdit.text = gluonPlayerAdapter.serviceProvider.password;
    }

    function loggedIn()
    {
        busyWidget.visible = false
        busyWidget.running = false
        loginStatusLabel.text = "Logged In"
        loginStatusLabel.setIcon("dialog-ok-apply")
    }

    function loginFailed()
    {
        busyWidget.visible = false
        busyWidget.running = false
        loginStatusLabel.text = "Login failed"
        loginButton.enabled = true
    }
}
