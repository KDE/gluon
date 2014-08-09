import QtQuick 2.2
import QtQuick.Window 2.1  // needed for the Window component
import Gluon.Player.Desktop 0.72 as GluonPlayer

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
        anchors.fill:parent
        
        Repeater {
            id: rosterListView
            
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: chatStatus.top
            
            clip: true;
            
            model: GluonPlayer.RosterModel{ id: rosterModel }
            delegate: Text{ text: statusText }
        }
        
        Text {
            id: chatStatus
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            
            height: 15
            
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            
            text: "Currently offline"
            
            font.pixelSize: 13
            font.family: "Helvetica"
            
            color: design.txcolor
        }
    }
    
    Component.onCompleted:{
        xmppClient.onLoggedIn.connect(onLoggedIn);
        xmppClient.onLoggedOut.connect(onLoggedOut);
        
        //first time load
        load();
    }
}
 
