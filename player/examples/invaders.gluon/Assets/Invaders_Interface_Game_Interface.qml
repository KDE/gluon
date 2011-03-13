import QtQuick 1.0

Item {
    Rectangle {
        anchors.left: parent.left;
        anchors.top: parent.top;
        
        width: 200;
        height: 60;
        
        color: "#484C52";
        
        Text {
            id: livesLabel;
            
            anchors.left: parent.left;
            anchors.top: parent.top;
            anchors.leftMargin: 10;
            anchors.topMargin: 10;
            
            color: "#ffffff";
            
            text: "Lives:";
        }
        
        Row {
            anchors.left: livesLabel.right;
            anchors.leftMargin: 10;
            anchors.verticalCenter: livesLabel.verticalCenter;
            
            spacing: 5;
            
            Repeater {
                id: livesItems;
                model: Scene.lives;
                
                Image {
                    source: "image://texture/Invaders/Assets/Textures/spaceship.png"
                    width: 16;
                    height: 16;
                }
            }
        }
        
        Text {
            id: scoreLabel;
            
            anchors.left: parent.left;
            anchors.bottom: parent.bottom;
            anchors.leftMargin: 10;
            anchors.bottomMargin: 10;
            
            color: "#ffffff";
            
            text: "Score:";
        }
        
        Text {
            id: scoreText;
            
            anchors.left: scoreLabel.right;
            anchors.leftMargin: 10;
            anchors.verticalCenter: scoreLabel.verticalCenter;
            
            color: "#ffffff";
            
            text: Game.score;
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
    
    Rectangle {
        id: gameOverScreen;
        
        anchors.fill: parent;
        
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
                
                font.pointSize: 32;
                font.bold: true;
                font.capitalization: Font.SmallCaps;
                
                color: "#ffffff";
                opacity: 0;
                
                text: "Game Over!";
            }
            
            Text {
                id: gameOverScoreText;
                
                anchors.horizontalCenter: parent.horizontalCenter;
                
                font.pointSize: 14;
                font.bold: true;
                font.capitalization: Font.SmallCaps;
                
                color: "#ffffff";
                opacity: 0;
                
                text: "You scored ... points.";
            }
            
            Text {
                id: gameOverResumeText;
               
                anchors.horizontalCenter: parent.horizontalCenter;
                
                font.pointSize: 14;
                font.bold: true;
                font.capitalization: Font.SmallCaps;
                
                color: "#ffffff";
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
            font.pointSize: 14;
            font.bold: true;
            font.capitalization: Font.SmallCaps;
            
            color: "#ffffff";
            
            states: State {
                name: "Current"
                when: ListView.isCurrentItem;
                PropertyChanges { target: button; color: "#ff0000"; }
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
        MessageHandler.subscribe("GameEnded", function() { gameOverScoreText.text = "You scored " + Game.score + " points"; gameOverScreen.opacity = 1; }, this);
    }
    
    function update() {
        livesItems.model = Scene.lives;
        scoreText.text = Game.score;
        
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
