import QtQuick 2.2
import QtQuick.Controls 1.1

import Gluon.Player.Desktop 0.72 as GluonPlayer

import "utils"

ApplicationWindow {
    id: mainWindow
    
    title: qsTr("Gluon Player (Desktop-Qt5)")
    width: 1024
    height: 768

    menuBar: GluonMenuBar{ id: gluonmenubar }
    statusBar: GluonStatusBar{ id: gluonstatusbar }
    
    Design{
        id:design
    }
    
    LoginModal{
        id: loginscreen
        z:1
    }
    
    ProfileWindow{
        id: profilescreen
        z:1
    }
    
    NotificationWindow{
        id: notification
        z:1
    }
    
    RegisterUser{
        id: registeruserscreen
        z:1
    }
    
    //xmpp client used to interact
    GluonPlayer.XmppClient{
        id: xmppClient
    }
    
    //object that represents self person both with OCS and XMPP
    GluonPlayer.SelfUser{
        id: self
    }
    
    //main background
    Background{
        
        //left area loader
        //only used for menu
        Loader{
            id: leftloader
            
            width: 100
            
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }
        
        //central area loader
        //used for content, games, comments etc
        Loader{
            id: centerloader
            
            anchors.left: leftloader.right
            anchors.right: rightloader.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            
            function showSingleGame(id){
                centerloader.setSource("center/singlegame/Game.qml",{"gameId":id});
            }
            function showHome(){
                centerloader.setSource("center/main.qml");
            }
            function showSocial(){
                centerloader.setSource("center/social/Social.qml");
            }
        }
        
        //right area for modal
        //used for user management, social etc
        Loader{
            id: rightloader
            
            width: 300
            
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }
    }
    Component.onCompleted: {
        centerloader.source = "center/main.qml";
        leftloader.source = "left/main.qml";
        rightloader.source = "right/main.qml";
    }
}
