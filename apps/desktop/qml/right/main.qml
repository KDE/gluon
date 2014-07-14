import QtQuick 2.2
import Gluon.Player.Desktop 0.72 as GluonPlayer

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
        
        height: accolumn.height+50
        
        Column{
            id:accolumn
            spacing: 10
            
            anchors.top: parent.top
            anchors.topMargin: 20
            
            height: childrenRect.height
            width: parent.width
            
            Text{
                anchors.left:  parent.left
                anchors.leftMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 20
                text: "Social Stream"
                font.pointSize: 20
                color: design.txcolor
            }
            
            Text{
                id: personsnothingfound_ac
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.leftMargin: 20
                color: design.txcolor
                text: "Nothing found."
            }
            
            Repeater {
                id: activityListView
                
                height: childrenRect.height
                
                //needed for children width
                width: parent.width
                
                function setLogged(){
                    activitymodel.fetchActivities();
                }
                
                function ifEmpty(){
                    if(activityListView.count==0){
                        personsnothingfound_ac.visible = true;
                    } else {
                        personsnothingfound_ac.visible = false;
                    }
                }
                
                onItemAdded:{
                    ifEmpty();
                }
                onItemRemoved:{
                    ifEmpty();
                }
                
                Component.onCompleted:{
                    loginscreen.onLoginCompleted.connect(setLogged);
                    ifEmpty();
                }
                
                model: GluonPlayer.ActivityModel{ id:activitymodel }
                delegate: ActivityDelegate{ }
            }
        }
    }
    
    Box{
        width: parent.width
        
        height: frcolumn.height+50
        
        Column{
            id:frcolumn
            spacing: 10
            
            anchors.top: parent.top
            anchors.topMargin: 20
            
            height: childrenRect.height
            width: parent.width
            
            Text{
                anchors.left:  parent.left
                anchors.leftMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 20
                text: "Friend requests"
                font.pointSize: 20
                color: design.txcolor
            }
            
            Text{
                id: personsnothingfound_fr
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.leftMargin: 20
                color: design.txcolor
                text: "Nothing found."
            }
            
            Repeater {
                id: friendRequestListView
                
                height: childrenRect.height
                
                //needed for children width
                width: parent.width
                
                function setLogged(){
                    model.fetchRequests();
                }
                
                Component.onCompleted:{
                    loginscreen.onLoginCompleted.connect(setLogged);
                }
                
                model: GluonPlayer.FriendRequestModel { id: friendRequestModel }
                delegate: FriendRequestDelegate{ }
                
                onItemAdded:{
                    if(friendRequestListView.count==0){
                        personsnothingfound_fr.visible = true;
                    } else {
                        personsnothingfound_fr.visible = false;
                    }
                }
                onItemRemoved:{
                    if(friendRequestListView.count==0){
                        personsnothingfound_fr.visible = true;
                    } else {
                        personsnothingfound_fr.visible = false;
                    }
                }
            }
        }
    }
    
}