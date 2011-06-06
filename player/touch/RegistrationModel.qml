/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

 ListModel {
     ListElement {
         identifierText: "regUsernameText"
         identifierLineEdit: "regUsernameLineEdit"
         textdata: "Login"
     }
     ListElement {
         identifierText: "regFirstNameText"
         identifierLineEdit: "regFirstNameLineEdit"
         textdata: "First name"
     }
     ListElement {
         identifierText: "regLastNameText"
         identifierLineEdit: "regLastNameLineEdit"
         textdata: "Lasst name"
     }
     ListElement {
         identifierTextt: "regEmailText"
         identifierLineEdit: "regEmailLineEdit"
         textdata: "Email"
     }
     ListElement {
         identifierText: "regRepeatEmailText"
         identifierLineEdit: "regRepeatEmailLineEdit"
         textdata: "Repeat email"
     }
     ListElement {
         identifierText: "regPasswordText"
         identifierLineEdit: "regPasswordLineEdit"
         textdata: "Password"
     }
     ListElement {
         identifierText: "regRepeatPasswordText"
         identifierLineEdit: "regRepeatPasswordLineEdit"
         textdata: "Repeat password"
     }
 }
