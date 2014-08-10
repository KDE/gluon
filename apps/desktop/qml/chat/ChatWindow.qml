import QtQuick 2.2
import QtQuick.Window 2.1  // needed for the Window component
import Gluon.Player.Desktop 0.72 as GluonPlayer

import "../utils"

Window {
    id: chatWindow
    width: 350
    height: 485
    
    title: "Friends - Gluon Player"
    
    Background {
        anchors.fill:parent
        
        //set states here, Window component doesn't support states
        states: [
            State {
                name: "logged";
                when: xmppClient.logged == true;
                PropertyChanges { target: chatStatus; visible: false }
                PropertyChanges { target: chatMyName; text: self.username }
                PropertyChanges { target: chatImageStatus; source: "../resources/chatgreen.png" }
                PropertyChanges { target: chatHeaderStatus; text: "(Online)" }
            },
            State {
                name: "notlogged"
                when: xmppClient.logged == false;
                PropertyChanges { target: chatStatus; text: "You're offline! Please log in on Gluon Desktop!" }
                PropertyChanges { target: chatMyName; text: "anonymous" }
                PropertyChanges { target: chatImageStatus; source: "../resources/chatgray.png" }
                PropertyChanges { target: chatHeaderStatus; text: "(Offline)" }
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
                
                color: design.txcolor
                verticalAlignment: Text.AlignVCenter
            }
            
            Text{
                id: chatHeaderStatus
                
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: chatMyName.right
                anchors.leftMargin: 10
                
                color: design.midcolor
                verticalAlignment: Text.AlignVCenter
            }
        }
        
        Line{
            id: chatSeparator
            anchors.top: chatHeader.bottom
            
            color: design.bgdarkcolor
        }
        
        ListView {
            id: rosterListView
            
            anchors.top: chatSeparator.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            
            clip: true;
            
            model: GluonPlayer.RosterModel{ id: rosterModel }
            delegate: ContactDelegate{ }
        }
        
        //text shown in case we're offline
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
    }
}
 
