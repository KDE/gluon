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
    id: topmost;

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
        function onCreation(){viewport.state= 'default'}

        Timer {
            id: viewportTimer
            interval: 2000
            onTriggered:{viewport.onCreation();}
        }

        IntroSlideShow {
            id :animator;
            Component.onCompleted:viewportTimer.start();
        }

        CustomText{
            id :custom;
        }

        width: animator.width;
        height: animator.height;
        x: animator.x;
        y: animator.y;

        Behavior on width { NumberAnimation { duration: 500; } }
        Behavior on height { NumberAnimation { duration: 500; } }
        Behavior on x { NumberAnimation { duration: 500; } }
        Behavior on y { NumberAnimation { duration: 500; } }

        Rectangle{
            id: textBox;
            color: "Transparent";
            opacity: 1;
            property bool showText: false ;
            width: topmost.width / 4;
            height: topmost.height /6;
            x: topmost.width / 5;
            y: topmost.height / 5;
            states: [

                State {
                    name: "top"
                    AnchorChanges {
                                target: textBox;
                                anchors.top: viewport.bottom;
                                anchors.horizontalCenter: viewport.horizontalCenter;
                    }
                    PropertyChanges { target:textBox; anchors.topMargin: 10}
                },

                State {
                    name: "bottom"
                    AnchorChanges {
                                target: textBox;
                                anchors.bottom: viewport.top;
                                anchors.horizontalCenter: viewport.horizontalCenter

                    }
                    PropertyChanges { target:textBox; anchors.bottomMargin: 10}

                },

                State {
                    name: "right"
                    AnchorChanges {
                                target: textBox;
                                anchors.left: viewport.right;
                                anchors.verticalCenter: viewport.verticalCenter;

                    }
                    PropertyChanges { target:textBox; anchors.leftMargin: 10}

                },

                State {
                    name: "left"
                    AnchorChanges {
                                target: textBox;
                                anchors.right: viewport.left;
                                anchors.verticalCenter: viewport.verticalCenter;

                    }
                    PropertyChanges { target:textBox; anchors.rightMargin: 10}
                }
            ]

            Text {
                id : docktext;
                width: parent.width
                font.pointSize: 12;
                font.bold : true;
                font.italic: true;
                font.letterSpacing: 1;
                text: "";
                style: Text.Raised;
                color: "white";
                wrapMode :Text.Wrap;
                anchors.fill: textBox;

              }

            function updateText(which)
            {   docktext.text=(function() { return custom.getText(which); })
            }

            function orient() {
                if (((animator.tRightMain() - animator.tRightDock()) > textBox.width)&&(animator.dHeight()-textBox.height > 0))
                {
                    textBox.state = 'right';
                }

                else if(((animator.dX()-animator.mX()) > textBox.width)&&(animator.dHeight()-textBox.height > 0))
                {
                     textBox.state = 'left';
                }

                else if (((animator.dY()-animator.mY()) > textBox.height)&&(animator.dWidth()- textBox.width >0))
                {
                        textBox.state = 'bottom';
                }

                else
                {
                    textBox.state = "top";
                }

                show();

            }

            function show()
            {   textBox.opacity=1;
                showText = true ;
            }

            Behavior on opacity {
                    NumberAnimation { properties:"opacity"; duration: 500 }
             }

        }


        states: [

        State {
                name: "default"
                PropertyChanges { target:animator; dockername: "ComponentsDock"}
                StateChangeScript {
                         name: "myScript"
                         script: { textBox.orient();textBox.updateText("default"); showTimer.stop();}

                }
          },

        State {
                name: "project"
                PropertyChanges { target:animator; dockername : "ProjectDock"}
                StateChangeScript {
                         name: "myScript"
                         script: { textBox.orient();textBox.updateText("project");showTimer.stop();}

                }
            },

        State {
                name: "message"
                PropertyChanges { target:animator; dockername : "MessageDock"}
                StateChangeScript {
                         name: "myScript"
                         script: { textBox.orient();textBox.updateText("message");showTimer.stop();}

                }
            },

        State {
                name: "scene"
                PropertyChanges { target:animator; dockername : "SceneDock"}
                StateChangeScript {
                         name: "myScript"
                         script: { textBox.orient();textBox.updateText("scene");showTimer.stop();}

                }
            },

        State {
                name: "property"
                PropertyChanges { target:animator; dockername : "PropertiesDock"}
                StateChangeScript {
                         name: "myScript"
                         script: { textBox.orient();textBox.updateText("property");showTimer.stop();}

                }
            }
        ]

    }


    MouseArea {

        id : mouseArea;

        Timer {
            id: showTimer
            interval: 500
            onTriggered:  {

                 switch(animator.dockername){

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
                                   viewport.state = 'default';
                                   break;

                               default:
                                   break;

            }

        }

    }

        anchors.fill: parent;
        onClicked: {
            if(textBox.showText){ textBox.opacity = 0 ;}
            showTimer.start();

        }

    }

}
