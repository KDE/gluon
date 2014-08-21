import QtQuick 2.2
import QtQuick.Window 2.1  // needed for the Window component
import Gluon.Player.Desktop 0.72 as GluonPlayer
import QtQuick.Controls 1.1

import "../utils"

Window {
    id: conversationWindow
    width: 350
    height: 485
    
    property string jid;
    
    title: "Chat with "+ jid +" - Gluon Player"
    
    function addMessage(state, body){
        if(body){
            chatMessagesModel.append({"body": "<"+jid+">: "+body});
            show();
        } else {
            if(state==4){
                chatStatus.text = "(Composing)";
            } else if(state==1) {
                chatStatus.text = "(Active)";
            }
        }
    }
    
    function setPresence(presence){
        chatImageStatus.state = presence;
    }
    
    function addSelfMessage(body){
        if(body){
            chatMessagesModel.append({"body": "<"+self.username+">: "+body});
            show();
        }
    }
    
    Background {
        anchors.fill:parent
        
        //set states here, Window component doesn't support states
        states: [
            State {
                name: "logged";
                when: xmppClient.logged == true;
                PropertyChanges{ target: isWritingTimer; running: true }
            },
            State {
                name: "notlogged"
                when: xmppClient.logged == false;
                PropertyChanges{ target: isWritingTimer; running: false }
            }
        ]
        
        state: "notlogged"
        
        Rectangle{
            id: chatHeader
            
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            
            height: 35
            
            color: design.fgcolor
            
            Image{
                id: chatImageStatus
                
                property string presence: "offline"
                
                states: [
                    State{
                        name: "online"
                        when: presence == "online"
                        PropertyChanges{ target: chatImageStatus; source: "../resources/chatgreen.png" }
                    },
                    State{
                        name: "away"
                        when: presence == "away"
                        PropertyChanges{ target: chatImageStatus; source: "../resources/chatorange.png" }
                    },
                    State{
                        name: "busy"
                        when: presence == "busy"
                        PropertyChanges{ target: chatImageStatus; source: "../resources/chatred.png" }
                    },
                    State{
                        name: "offline"
                        when: presence == "offline"
                        PropertyChanges{ target: chatImageStatus; source: "../resources/chatgray.png" }
                    }
                ]
                
                state: "offline"
                
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                
                anchors.leftMargin: 10
                anchors.topMargin: 10
                anchors.bottomMargin: 10
                
                width: height
            }
            
            Text{
                id: chatMyName
                   
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: chatImageStatus.right
                anchors.leftMargin: 10
                
                text: jid
                
                color: design.txcolor
                verticalAlignment: Text.AlignVCenter
            }
            
            Text{
                id: chatStatus
                
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: chatMyName.right
                anchors.leftMargin: 10
                
                text: "(Active)"
                
                color: design.txcolor
                verticalAlignment: Text.AlignVCenter
            }
        }
        
        Line{
            id: chatSeparator
            anchors.top: chatHeader.bottom
            
            color: design.bgdarkcolor
        }
        
        ListModel{ id: chatMessagesModel }
        
        ListView{
            anchors.top: chatSeparator.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: sendMessageButton.top
            
            model: chatMessagesModel
            
            delegate: Text{ 
                text: body
                
                font.pixelSize: 15
                
                width: parent.width
                
                color:design.txcolor
                
                wrapMode: Text.WordWrap
            }
        }
        
        TextField {
            id: messageArea
            
            property int previousLength: 0;
            property string previousState: "active";
            
            anchors.top: sendMessageButton.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            
            style: DesignTextField{}
            
            //NEEDS PORT
            Keys.onReturnPressed:{
                conversationWindow.addSelfMessage(text);
                xmppClient.sendConversationMessage(text,jid+"@myhost.io");
                //clear textbox
                text = "";
            }
            
            /**
             * Send status messages depenant on if the user is typing or not
             */
            Timer {
                id: isWritingTimer
                interval: 3000
                repeat: true
                running: true
                onTriggered: {
                    if (messageArea.previousLength!=messageArea.length) {
                        if(messageArea.previousState!="composing"){
                            xmppClient.sendStatusMessage(jid+"@myhost.io", "composing");
                            messageArea.previousState = "composing";
                        }
                        messageArea.previousLength = messageArea.length;
                    } else {
                        if(messageArea.previousState!="active"){
                            xmppClient.sendStatusMessage(jid+"@myhost.io", "active");
                            messageArea.previousState = "active";
                        }
                    }
                }
            }
            
        }
        
        Button {
            id: sendMessageButton
            
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            
            text: "Send"
            style: DesignButton{}
            onClicked:{
                conversationWindow.addSelfMessage(text);
                xmppClient.sendConversationMessage(text,jid+"@myhost.io");
                messageArea.text = "";
            }
        }
        
        //text shown in case we're offline
        /* riusa se necessario
        Text {
            id: chatStatus
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            
            anchors.bottomMargin: 10
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.topMargin: 10
            
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            
            text: "You're offline! Please log in on Gluon Desktop!";
            
            font.pixelSize: 25
            font.family: "Arial"
            
            wrapMode: Text.WordWrap
            
            color: design.txcolor
        }
        */
    }
}
 
