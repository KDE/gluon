import QtQuick 1.0

Item {
    id:base;
    
    Rectangle {
        anchors.left: parent.left;
        anchors.top: parent.top;
        
        width: parent.width / 5;
        height: parent.height / 5;

        color: "#336633";

        Grid {
            anchors.centerIn: parent;
            //anchors.verticalCenter: parent.verticalCenter;
            
            columns: 2;
            spacing: 10;

            Text {
                text: "Score:";
                color: "#990000"
            }

            Text {
                id: scoreText;
                color: "#990000"
                text: Scene.score ? Scene.score : "0";
            }

            Text {
                text: "Health:";
                color: "#990000"
            }

            Text {
                id: healthText;
                text: Scene.currentHealth ? Scene.currentHealth : "100";
                color: "#990000"
            }
        }
    }

    Rectangle {
        id: gameOverScreen;

        anchors.fill: parent;

        property alias text: gameOverScoreText.text;

        opacity: 0;
        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }

        color: "#000000";

        Column {
            anchors.centerIn: parent;
            Text {
                id: gameOverText;

                anchors.horizontalCenter: parent.horizontalCenter;

                font {
                    pointSize: 32;
                    bold: true;
                    capitalization: Font.SmallCaps;
                }

                color: "#990000";
                opacity: 0;

                text: "Game Over!";
            }

            Text {
                id: gameOverScoreText;

                anchors.horizontalCenter: parent.horizontalCenter;

                font {
                    pointSize: 14;
                    bold: true;
                    capitalization: Font.SmallCaps;
                }

                color: "#990000";
                opacity: 0;

                text: "You scored ... points.";
            }

            Text {
                id: gameOverResumeText;

                anchors.horizontalCenter: parent.horizontalCenter;

                font {
                    pointSize: 14;
                    bold: true;
                    capitalization: Font.SmallCaps;
                }

                color: "#990000";
                opacity: 0;

                text: "Press \"Enter\" to try again.";
            }

            states: [
                State {
                    name: "visible";
                    when: gameOverScreen.opacity == 1;
                    PropertyChanges { target: gameOverText; opacity: 1; }
                    PropertyChanges { target: gameOverScoreText; opacity: 1; }
                    PropertyChanges { target: gameOverResumeText; opacity: 1; }
                }
            ]

            transitions: [
                Transition {
                    SequentialAnimation {
                        ParallelAnimation {
                            NumberAnimation { target: gameOverText; property: "scale"; from: 10; to: 1; duration: 1000 }
                            NumberAnimation { target: gameOverText; property: "opacity"; duration: 250; }
                        }
                        NumberAnimation { target: gameOverScoreText; property: "opacity"; duration: 500; }
                        NumberAnimation { target: gameOverResumeText; property: "opacity"; duration: 500; }
                    }
                }
            ]
        }
    }

     Item {
        id: pauseScreen;

        anchors.fill: parent;

        opacity: 0;
        Behavior on opacity {
            NumberAnimation { duration: 250 }
        }

        Rectangle {
            width: parent.width;
            height: parent.height;

            color: "#000000";
            opacity: 0.5;
        }

        ListView {
            id: pauseScreenButtons;

            anchors.centerIn: parent;

            width: parent.width / 2;
            height: 150;
            spacing: 10;

            currentIndex: 0;
            keyNavigationWraps: true;

            model: buttonModel;
            delegate: buttonDelegate;
        }
    }
    
    ListModel {
        id: buttonModel;

        ListElement {
            buttonText: "Return to Game";
            buttonTriggered: "pauseScreen.opacity = 0; Scene.paused = false;"
        }

        ListElement {
            buttonText: "Restart";
            buttonTriggered: "Scene.resetting = true; Game.resetCurrentScene();"
        }

//         ListElement {
//             buttonText: "Quit to Menu"
//             buttonTriggered: "Game.setCurrentScene(\"Invaders/Scenes/Menu\");"
//         }
        ListElement {
            buttonText: "Quit to System"
            buttonTriggered: "Game.stopGame();"
        }
    }

    Component {
        id: buttonDelegate;

        Text {
            id: button;
            anchors.horizontalCenter: parent.horizontalCenter;

            text: buttonText;
            font {
                pointSize: 14;
                bold: true;
                capitalization: Font.SmallCaps;
            }

            color: "#339933";

            MouseArea {
                anchors.fill: parent;
                onPressed: eval(buttonTriggered);
            }

            states: State {
                name: "Current"
                when: ListView.isCurrentItem;
                PropertyChanges { target: button; color: "#990000"; }
            }

            transitions: Transition {
                ColorAnimation { target: button; properties: "color"; duration: 200; }
            }

            function trigger() {
                eval(buttonTriggered);
            }
        }
    }

    Component.onCompleted: {
        MessageHandler.subscribe("playerDied", function() { gameOverScreen.text = "You killed " + Scene.score + " goblins!"; gameOverScreen.opacity = 1; }, base);
    }

    function update() {
        healthText.text = Scene.currentHealth;
        scoreText.text = Scene.score;

        if(GameObject.Key_Escape.isActionStarted())
        {
            if(pauseScreen.opacity < 1)
            {
                Scene.paused = true;
                pauseScreen.opacity = 1;
            }
            else
            {
                pauseScreen.opacity = 0;
                Scene.paused = false;
            }
        }

        if(GameObject.Key_Up.isActionStarted() && pauseScreen.opacity > 0)
        {
            pauseScreenButtons.decrementCurrentIndex();
        }

        if(GameObject.Key_Down.isActionStarted() && pauseScreen.opacity > 0)
        {
            pauseScreenButtons.incrementCurrentIndex();
        }

        if(GameObject.Key_Return.isActionStarted())
        {
            if(pauseScreen.opacity > 0)
            {
                pauseScreenButtons.currentItem.trigger();
            }
            else if(gameOverScreen.opacity > 0)
            {
                gameOverScreen.opacity = 0;
                Scene.resetting = true;
                Game.resetCurrentScene();
            }
        }
    }
}