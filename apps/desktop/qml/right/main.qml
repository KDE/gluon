import QtQuick 2.2

import "../utils"
import "userbox"

Column{
    anchors.fill:parent
    
    Box{
        width: parent.width
        
        Component.onCompleted:{
            height = childrenRect.height +40
        }
        
        Logged{
            anchors.top: parent.top
            anchors.topMargin: 20
            
            height: childrenRect.height
        }
    }
    
    Box{
        width: parent.width
        
        Component.onCompleted:{
            height = childrenRect.height +40
        }
        
        NotLogged{
            anchors.top: parent.top
            anchors.topMargin: 20
            
            height: childrenRect.height
        }
    }
    
    Box{
        width: parent.width
        
        Component.onCompleted:{
            height = childrenRect.height +40
        }
        
        Text{
            id:activitywindow
            anchors.left:  parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
            text: "Friends' activity"
            font.pointSize: 20
            color: design.txcolor
        }
    }
}