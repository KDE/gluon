import QtQuick 2.2

import "../utils"
import "userbox"

Column{
    anchors.fill:parent
    
    Box{
        id: userbox_bg
        width: parent.width
        
        states:[
            State {
                name: "logged"
                PropertyChanges { target: userbox; source: "userbox/Logged.qml" }
            },
            State {
                name: "notlogged"
                PropertyChanges { target: userbox; source: "userbox/NotLogged.qml" }
            }
        ]
        
        function setHeight(h){
            height = h;
        }
        
        function setLogged(){
            state = "logged";
        }
        
        function setNotLogged(){
            state = "notlogged";
        }
        
        Component.onCompleted:{
            loginscreen.onLoginCompleted.connect(setLogged);
            loginscreen.onLoginFail.connect(setNotLogged);
            loginscreen.onLogoutCompleted.connect(setNotLogged);
            
            state = "notlogged";
        }
        
        Loader{
            id: userbox
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right:parent.right
            
            anchors.topMargin: 20
            anchors.leftMargin: 20
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