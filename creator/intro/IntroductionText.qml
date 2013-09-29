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

Item {
    property variant items: {
        'Start': qsTr("Welcome to Gluon Creator. This quick tour will give a brief introduction of the main UI elements in Gluon Creator."),
        'ComponentsDock': qsTr("This is a list of the pre-defined functionality available to you in Gluon Creator. The Components are things like sound emitters and listeners, camera controllers, input handlers and the like, as well as the custom logic handler, the Scripting component."),
        'ProjectDock': qsTr("This shows all the Assets that you have in your project, such as sounds, textures, scripts, materials and Scenes."),
        'MessageDock': qsTr("This is where debugging messages, errors from scripts and other information from the various Components are shown."),
        'SceneDock': qsTr("The contents of the current Scene. This is made up of a tree of GameObjects which in essence is your scene graph."),
        'PropertiesDock': qsTr("The place where you can see and manipulate every option on the various Components which are attached to the GameObjects in your game."),
        'End': qsTr("That's it! We hope you enjoy Gluon Creator!")
    }

    function text( index ){
        return items[index];
    }
}
