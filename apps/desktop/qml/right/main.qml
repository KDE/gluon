import QtQuick 2.2
import Gluon.Player.Desktop 0.72 as GluonPlayer

import "../utils"
import "userbox"

Box{
    id: rightcolumn
    anchors.fill:parent
    
    states:[
        State {
            name: "logged"
            when: self.logged == true
            PropertyChanges { target: userbox; source: "userbox/Logged.qml" }
        },
        State {
            name: "notlogged"
            when: self.logged == false
            PropertyChanges { target: userbox; source: "userbox/NotLogged.qml" }
        }
    ]
    
    state: "notlogged"
    
    Loader{
        id: userbox
        
        anchors.top: rightcolumn.top
        anchors.left: parent.left
        anchors.right:parent.right
        
        anchors.topMargin: 20
        anchors.leftMargin: 20
        
        height: 150
    }
    
    Line{ anchors.top: accolumn.top}
    
    Column{
        id:accolumn
        spacing: 10
        
        anchors.top: userbox.bottom
        anchors.topMargin: 20
        anchors.bottom: frcolumn.top
        anchors.bottomMargin: 20
        
        //height: (parent.height-202)*0.5
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
            
            visible: activitymodel.empty
        }
        
        Repeater {
            id: activityListView
            
            height: childrenRect.height
            
            //needed for children width
            width: parent.width
            
            model: GluonPlayer.ActivityModel{ id:activitymodel }
            delegate: ActivityDelegate{ }
        }
    }
    
    Line{ anchors.top: frcolumn.top}
    
    Column{
        id:frcolumn
        spacing: 10
        
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        
        height: (parent.height-userbox.height+2)*0.5
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
            
            visible: friendRequestModel.empty
        }
        
        Repeater {
            id: friendRequestListView
            
            height: childrenRect.height
            
            //needed for children width
            width: parent.width
            
            model: GluonPlayer.FriendRequestModel { id: friendRequestModel }
            delegate: FriendRequestDelegate{ }
        }
    }
    
}