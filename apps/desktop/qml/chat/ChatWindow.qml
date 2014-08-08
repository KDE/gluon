import QtQuick 2.2
import QtQuick.Window 2.1  // needed for the Window component

import "../utils"

Window {
    id: chatWindow
    width: 400
    height: 400
    
    title: "Friend chat - Gluon Player"
    
    function load(){
        if(xmppClient.isLogged()){
            onLoggedIn();
        } else {
            onLoggedOut();
        }
    }
    
    function onLoggedIn(){
        chatStatus.text = "You're online!";
    }
    
    function onLoggedOut(){
        chatStatus.text = "You're offline!\nPlease log in on Gluon Desktop!";
    }
    
    Background {
        
        Box{ //box needs size and placement
            anchors.fill:parent
            
            Column{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                anchors.topMargin: 20
                anchors.bottomMargin: 20
                
                spacing: 10
                
                Text {
                    id: chatStatus
                    width: parent.width -20
                    horizontalAlignment: Text.AlignHCenter
                    
                    text: "Currently offline"
                    
                    font.pointSize: 9
                    font.family: "Helvetica"
                    
                    color: design.txcolor
                }
            }
        }
    }
    
    Component.onCompleted:{
        xmppClient.onLoggedIn.connect(onLoggedIn);
        xmppClient.onLoggedOut.connect(onLoggedOut);
        
        //first time load
        load();
    }
}
 
