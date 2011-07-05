/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

/**
 * \page creator Gluon Creator
 *
 * \todo Screenshot of creator
 *
 * In the image to the right you can see Gluon Creator in its default layout, with the Invaders
 * sample loaded. In a rough clock-wise order, the elements of the window are:
 *
 * - <b>Project</b>
 *      - This shows all the Assets that you have in your project, such as sounds, textures, scripts
 *        and Scenes.
 * - <b>Components</b>
 *      - This is a list of the pre-defined functionality available to you in Gluon Creator. The
 *        Components are things like sound emitters and listeners, camera controllers, input
 *        handlers and the like.
 * - <b>View</b>
 *      - This is the view of your current Scene from the perspective of the camera.
 * - <b>Scene</b>
 *      - The contents of the current Scene - in essence your scene graph.
 * - <b>Properties</b>
 *      - The place where you can see and manipulate every option on the various Components which
 *        are attached to the GameObjects in your game.
 * - <b>Messages</b>
 *      - This is where debugging messages, errors from scripts and other information from the
 *        various Components are shown.
 *
 * \section creator-basics Basics of Using Gluon Creator
 *
 * The work flow of using Gluon Creator to create games is based around the idea that you should be
 * able to use your mouse for as much of the work as possible. As such, adding an Asset to your
 * project is a task done by dragging a file into the Project pane from your file browser (or
 * alternatively by clicking the Add Asset... button in the toolbar). It will then be copied to
 * the project folder, and be made available for use in your game.
 *
 * To describe a scene in a game, you select the appropriate Scene in the Project view, which causes
 * it to be loaded and shown in the Scene pane, and in the View the camera view will show what the
 * camera sees in the newly loaded scene. You can now edit this scene, by adding and removing
 * GameObject to the Scene, and by adding Components to those GameObjects.
 * To add a GameObject to the scene, click on the Add GameObject button on the toolbar. This will
 * add a new, empty GameObject to the Scene, and if you have an existing GameObject selected, the
 * new one will be added as a child to the selected one. This allows you, as described in Gluon
 * Basics, to build items for the game based on multiple GameObjects in a hierarchy, which all move
 * along with each other.
 *
 * So that you can change the values for the various Components, selecting a GameObject in the Scene
 * view will make the properties for that object and all the Components on it show up in the
 * Properties view, which is a scrollable, categorized list of all the various properties.
 *
 * One of the functions which will be performed with some regularity from the Properties view is
 * that of setting references to various Assets, for example setting the texture of a
 * SpriteRenderer, or the sound of a SoundEmitter. This is done by clicking on the ... button in the
 * Properties view and selecting the appropriate item from the list.
 */

