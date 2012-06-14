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


        IntroSlideShow {
                id :animator;
                dockername: "ComponentsDock";
        }

        id: viewport;
        width: animator.implicitWidth;
        height: animator.implicitHeight;
        x: animator.x;
        y: animator.y;

        Behavior on width { NumberAnimation { duration: 500; } }
        Behavior on height { NumberAnimation { duration: 500; } }
        Behavior on x { NumberAnimation { duration: 500; } }
        Behavior on y { NumberAnimation { duration: 500; } }


        Text {
            id : text;
            font.pointSize: 12;
            font.bold : true;
            text: "test";
            opacity: 0;
            style: Text.Raised;
            color: "white";
            property bool showText: true ;

            states: [

            State {
                    name: "right"
                    AnchorChanges {
                                target: text
                                anchors.left: viewport.right;

                            }
              },

            State {
                    name: "left"
                    AnchorChanges {
                                target: text
                                anchors.right: viewport.left;

                            }

                }
]


            function orient() {

                if ((animator.getdockX() +animator.getdockWidth()) < (animator.getrefWidth())){
                    text.state = "right";
                     console.log("dockname is");
                    console.log(animator.dockername);
                }
                 else{
                    text.state = "left";
                    console.log("dockname is");
                    console.log(animator.dockername);
                }
                show();

            }

            function show(){opacity=1; showText = false ;}

            Behavior on opacity {
                    NumberAnimation { properties:"opacity"; duration: 100 }
         }
    }

        MouseArea {

            Timer {
                id: showTimer
                property int count: 0;
                interval: 500
                onTriggered:  {

                     switch(animator.dockername){

                                   case(""):
                                   {console.log("HAHAHAHAHHA");
                                       viewport.state = 'component';
                                   }
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

            }

        }

            anchors.fill: parent;
            onClicked: {
                if(!text.showText){ text.opacity = 0 ;}
                showTimer.start();

            }

        }


        states: [

        State {
                name: "component"
                PropertyChanges { target:animator; dockername: "ComponentsDock"}
                StateChangeScript {
                         name: "myScript"
                         script: { text.orient(); showTimer.stop();}

                }
          },

        State {
                name: "project"
                PropertyChanges { target:animator; dockername : "ProjectDock"}
                StateChangeScript {
                         name: "myScript"
                         script: { text.orient();showTimer.stop();}

                }
            },

        State {
                name: "message"
                PropertyChanges { target:animator; dockername : "MessageDock"}
                StateChangeScript {
                         name: "myScript"
                         script: { text.orient();showTimer.stop();}

                }
            },

        State {
                name: "scene"
                PropertyChanges { target:animator; dockername : "SceneDock"}
                StateChangeScript {
                         name: "myScript"
                         script: { text.orient();showTimer.stop();}

                }
            },

        State {
                name: "property"
                PropertyChanges { target:animator; dockername : "PropertiesDock"}
                StateChangeScript {
                         name: "myScript"
                         script: { text.orient();showTimer.stop();}

                }
            }
    ]

    transitions: [

            Transition {
                from: "*"; to: "*"
                NumberAnimation { properties: "x,y,width,height"; duration: 500 }
                 ScriptAction { scriptName: "myScript" }
            }
        ]


}

}
