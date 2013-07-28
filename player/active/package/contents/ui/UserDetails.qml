/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

import QtQuick 1.1
import org.kde.plasma.components 0.1 as PlasmaComponents

PlasmaBackground {

    PlasmaComponents.BusyIndicator {
        id: loginBusyIndicator
        anchors.centerIn: parent
        width: 64; height: width
        visible: false
    }

    PlasmaComponents.Label {
        id: usernameLabel
        anchors.fill: parent
        font.pointSize: 42
    }

    PlasmaComponents.Button {
        id: loginButton
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10

        iconSource: "dialog-password"
        height: 32
        width: height

        onClicked: loginDialog.open()
    }

    PlasmaComponents.Dialog {
        id: loginDialog
        width: 256; height: 96

        buttons: PlasmaComponents.Button {
            height: 32; width: loginDialog.width
            text: "Login"
            onClicked: loginDialog.accept()
        }
        content: Column {
            height: 64; width: loginDialog.width
            PlasmaComponents.TextField {
                id: loginUsernameText
                height: parent.height/2; width: parent.width
                placeholderText: "username"
            }
            PlasmaComponents.TextField {
                id: loginPasswordText
                height: parent.height/2; width: parent.width
                placeholderText: "password"
                echoMode: TextInput.Password
            }
        }

        onAccepted: {
            showBusy()
            usernameLabel.text = "Logging in"
            serviceProvider.login(loginUsernameText.text, loginPasswordText.text)
        }
    }

    Component.onCompleted: {
        serviceProvider.loginFinished.connect(loginFinished)
        serviceProvider.loginFailed.connect(loginFailed)
    }

    function loginFinished()
    {
        usernameLabel.text = serviceProvider.username
        hideBusy()
    }

    function loginFailed()
    {
        usernameLabel.text = "Error, please try again"
        hideBusy()
    }

    function showBusy()
    {
        loginBusyIndicator.running = true
        loginBusyIndicator.visible = true
    }

    function hideBusy()
    {
        loginBusyIndicator.running = false
        loginBusyIndicator.visible = false
    }
}