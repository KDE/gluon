import QtQuick 2.2
import QtQuick.Controls 1.1


import Gluon.Player.Desktop 0.72 as GluonPlayer
import "../utils"


GluonPlayer.SingleUser{
    id: singleuserdelegate
    anchors.left: parent.left
    anchors.leftMargin: 20
    anchors.right: parent.right
    anchors.rightMargin: 20
    
    height: 60
    width: parent.width
    
    property string pid: personid;
    
    onFriendRequestAccepted:{
        notification.open("Now you and "+username+" are friends!");
        friendRequestModel.fetchRequests();
    }
    
    onFriendRequestDeclined:{
        notification.open(""+username+"'s friend request declined.");
        friendRequestModel.fetchRequests();
    }
    
    Line{}
    
    Text{
        id:text
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        
        font.bold: true
        
        color: design.txcolor
        
        font.pointSize: 11.5
        
        text: personid
    }
    
    Button{
        id:button
        anchors.top: text.bottom 
        anchors.topMargin: 10
        anchors.left: parent.left
        style: DesignButton{ }
        text: "Accept"
        
        onClicked:{
            singleuserdelegate.username = singleuserdelegate.pid;
            singleuserdelegate.acceptFriendship();
        }
    }
    
    Button{
        id:button2
        anchors.top: text.bottom 
        anchors.topMargin: 10
        anchors.right: parent.right
        style: DesignButton{ }
        text: "Decline"
        
        onClicked:{
            singleuserdelegate.username = singleuserdelegate.pid;
            singleuserdelegate.declineFriendship();
        }
    }
    
}