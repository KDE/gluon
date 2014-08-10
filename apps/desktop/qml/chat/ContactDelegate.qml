import QtQuick 2.2

import "../utils"

Rectangle{
    id: chatHeader
    
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    
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
        
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        
        anchors.leftMargin: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        
        source: "../resources/chatgray.png"
        
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
    }
} 
