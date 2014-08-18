import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.1  // needed for the Window component

import Gluon.Player.Desktop 0.72 as GluonPlayer

import "utils"
import "chat"

ApplicationWindow {
    id: mainWindow
    
    title: qsTr("Gluon Player (Desktop-Qt5)")
    width: 1350
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
    
    Item{
        id: chatManager
        
        //rosterWindow prop
        property Window rosterWindow;
        property var conversations: new Array();
        
        //just open once roster
        function showRoster(){
            if(!rosterWindow){
                var rosterWindowComponent = Qt.createComponent("chat/ChatWindow.qml");
                rosterWindow = rosterWindowComponent.createObject(chatManager);
                rosterWindow.show();
            } else {
                rosterWindow.show();
            }
        }
        
        function openConversation(from){
            //if there's already an opened window
            for (var i=0; i<conversations.length; ++i) {
                if(conversations[i].jid==from){ //window found
                    conversations[i].show();
                    return;
                }
            }
            
            //if there's not, open new one, but only for incoming messages
            //not for status update
            var conversationComponent = Qt.createComponent("chat/ConversationWindow.qml");
            var conversation = conversationComponent.createObject(chatManager);
            conversations.push(conversation);
            conversation.jid = from;
            conversation.show();
        }
        
        function dispatchMessage(from, state, body){
            //if there's already an opened window
            for (var i=0; i<conversations.length; ++i) {
                
                if(conversations[i].jid==from){ //window found
                        conversations[i].addMessage(state, body);
                    return;
                }
            }
            
            //if there's not, open new one, but only for incoming messages
            //not for status update
            if(body){
                var conversationComponent = Qt.createComponent("chat/ConversationWindow.qml");
                var conversation = conversationComponent.createObject(chatManager);
                conversations.push(conversation);
                conversation.jid = from;
                conversation.addMessage(state,body);
            }
        }
    }
    
    //xmpp client used to interact
    GluonPlayer.XmppClient{
        id: xmppClient
        
        onNewMessage:{
            chatManager.dispatchMessage(from.split("@")[0], state, body);
        }
    }
    
    GluonPlayer.RosterModel{
        id: rosterModel
    }
    
    //object that represents self person both with OCS and XMPP
    GluonPlayer.SelfUser{
        id: self
    }
    
    //main background
    Background{
        
        Item{
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            
            anchors.topMargin: 3
            
            width: 1050
            
            anchors.horizontalCenter: parent.horizontalCenter
            
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
                
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                
                width: 350
            }
        }
    }
    Component.onCompleted: {
        //loading left, right and center part of Gluon Player
        centerloader.source = "center/main.qml";
        leftloader.source = "left/main.qml";
        rightloader.source = "right/main.qml";
    }
}
