import QtQuick 2.2

import "../utils"

Rectangle{
    id: chatHeader
    
    width: parent.width
    height: 35
    
    color: design.midcolor
    
    states: [
        State{
            name: "hovered"
            PropertyChanges{ target: chatHeader; color: design.fgcolor }
        }
    ]
    
    MouseArea{
        anchors.fill: parent
        
        hoverEnabled: true
        onEntered: { chatHeader.state = "hovered" }
        onExited: { chatHeader.state = "" }
    }
    
    Image{
        id: chatImageStatus
        
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
        
        text: statusText
        
        color: design.txcolor
        verticalAlignment: Text.AlignVCenter
        
        Component.onCompleted:{
            //delete domain part
            if(statusText){
                text = statusText.split("@")[0];
            }
        }
    }
} 
