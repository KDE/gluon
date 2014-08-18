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
            
        }
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
            },
            State {
                name: "notlogged"
                when: xmppClient.logged == false;
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
 
