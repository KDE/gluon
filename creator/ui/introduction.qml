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

import QtQuick 1.0
import Intro 1.0
Item {

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
        width: parent.width / 2;
        height: parent.height / 2;
        x: parent.width / 4;
        y: parent.height / 4;

        Behavior on width { NumberAnimation { duration: 500; } }
        Behavior on height { NumberAnimation { duration: 500; } }
        Behavior on x { NumberAnimation { duration: 500; } }
        Behavior on y { NumberAnimation { duration: 500; } }

            IntroSlideShow {
                id :animator;
    }

        Text {
            id : text;
            font.pointSize: 18;
            text: "test";
            style: Text.Raised;
            styleColor: "white";
            function orient() {
                console.log("IN ORIENT") ;
                if (animator.alignment == "left")
                {anchors.left= viewport.right;
                 anchors.right= viewport.left;
                }
                 else
                { anchors.right= viewport.left;
                }

            }
    }

        MouseArea {
            anchors.fill: parent;
            onClicked: {

                switch(animator.dockername){

                case(""):
                    viewport.state = 'component';
                    break;

                case("ComponentsDock"):
                    viewport.state = 'project';
                    break;

                case("ProjectDock"):
                    viewport.state = 'message';
                    break;

                case("MessageDock"):
                    viewport.state = 'scene';
                    break;

                case("SceneDock"):
                    viewport.state = 'property';
                    break;

                case("PropertiesDock"):
                    viewport.state = 'component';
                    break;

                default:
                    break;

                }


               onDockernameChanged: {
                        animator.setdockername(animator.dockername);
               }

                }

            }



        states: [

        State {
                name: "component"
                PropertyChanges { target:animator; dockername: "ComponentsDock"}
                PropertyChanges { target: viewport; x: animator.x; y: animator.y; width:animator.implicitWidth; height:animator.implicitHeight; toolTip: "Yeh hai component"}
                StateChangeScript {
                         name: "myScript"
                         script: { text.orient();}

                }
          },

        State {
                name: "project"
                PropertyChanges { target:animator; dockername : "ProjectDock"}
                PropertyChanges { target: viewport; x: animator.x; y: animator.y; width:animator.implicitWidth; height:animator.implicitHeight }
                StateChangeScript {
                         name: "myScript"
                         script: { text.orient();}

                }
            },

        State {
                name: "message"
                PropertyChanges { target:animator; dockername : "MessageDock"}
                PropertyChanges { target: viewport; x: animator.x; y: animator.y; width:animator.implicitWidth; height:animator.implicitHeight }
                StateChangeScript {
                         name: "myScript"
                         script: { text.orient();}

                }
            },

        State {
                name: "scene"
                PropertyChanges { target:animator; dockername : "SceneDock"}
                PropertyChanges { target: viewport; x: animator.x; y: animator.y; width:animator.implicitWidth; height:animator.implicitHeight }
                StateChangeScript {
                         name: "myScript"
                         script: { text.orient();}

                }
            },

        State {
                name: "property"
                PropertyChanges { target:animator; dockername : "PropertiesDock"}
                PropertyChanges { target: viewport; x: animator.x; y: animator.y; width:animator.implicitWidth; height:animator.implicitHeight }
                StateChangeScript {
                         name: "myScript"
                         script: { text.orient();}

                }
            }
    ]

    transitions: [

            Transition {
                from: "*"; to: "component"
                NumberAnimation { properties: "x,y,width,height"; duration: 1000 }
                 ScriptAction { scriptName: "myScript" }
            },

            Transition {
                from: "*"; to: "project"
                NumberAnimation { properties: "x,y,width,height"; duration: 1000 }
                ScriptAction { scriptName: "myScript" }
            },

            Transition {
                from: "*"; to: "message"
                NumberAnimation { properties: "x,y,width,height"; duration: 1000 }
                ScriptAction { scriptName: "myScript" }
            },

            Transition {
                from: "*"; to: "scene"
                NumberAnimation { properties: "x,y,width,height"; duration: 1000 }
                ScriptAction { scriptName: "myScript" }
            },

            Transition {
                from: "*"; to: "property"
                NumberAnimation { properties: "x,y,width,height"; duration: 1000 }
                ScriptAction { scriptName: "myScript" }
            }

        ]


}

}
