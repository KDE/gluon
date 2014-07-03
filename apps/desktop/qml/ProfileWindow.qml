import QtQuick 2.2
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.1

//gluon player specific imports
import Gluon.Player.Desktop 0.72 as GluonPlayer

import "utils"

GluonPlayer.SingleUser{
	id: window
	
	anchors.horizontalCenter: parent.horizontalCenter
	anchors.verticalCenter: parent.verticalCenter
	
	anchors.fill:parent
	
	onFriendRequestSent:{
        close();
        notification.open("Friend request sent!");
    }
    
    onFriendRequestFailed:{
        close();
        notification.open("Friend request failed!");
    }

    onFriendRequestAccepted:{
        notification.open("Now you and "+username+" are friends!");
    }
    
    onFriendRequestDeclined:{
        notification.open(""+username+"'s friend request declined.");
    }
	
	//open animation
	NumberAnimation on opacity {
        id: openAnimation
        from: 0
        to: 1
        duration: 175
        
        onRunningChanged: {
            if (openAnimation.running) {
                window.visible = true;
            }
        }
    }
    
    //close animation
    NumberAnimation on opacity {
        id: closeAnimation
        from: 1
        to: 0
        duration: 175
        onRunningChanged: {
            if (closeAnimation.running) {
                window.visible = true;
            } else {
                window.visible = false;
            }
        }
    }
	
	function open(){
		openAnimation.start();
        
        console.log("open window started");
	}
	
	function close(){
		closeAnimation.start();
        console.log("close window started");
	}
    
    //black bg rectangle
    Rectangle{
        anchors.fill: parent
        color: "#BB000000"
        
        MouseArea{
            anchors.fill: parent
            
            onClicked:{
                window.close()
            }
        }
    }
    
    GluonModalDialog{
        id : loginFormProxy;
        target: window_mainbox
        space: 20
        
        //here in order to prevent accidental close of modal
        //clicking inside modal but not on buttons
        MouseArea{
            anchors.fill: parent
        }
    }
        
    Column{
        id:window_mainbox
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        
        spacing: 15
        
        Label {
                font.pointSize: 27
                font.family: "Arial"
                anchors.left: window_maincolumn.left
                anchors.right: window_maincolumn.right
                
                anchors.bottomMargin: 10
                
                horizontalAlignment: Text.AlignHCenter
                
                text: "User Profile";
                color: design.txcolor;
                opacity: 1;
        }
        
        Grid {
            id: window_maincolumn;
            
            columns: 2
            spacing: 10
            
            //id
            Label {
                text: "Username:";
                color: design.txcolor;
                
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                id: m_username;
                color: design.txcolor
                font.bold: true
                text: username
            }
            
            //name
            Label {
                text: "Name:";
                color: design.txcolor;
            }
            Text {
                color: design.txcolor
                font.bold: true
                
                text: name
            }
            
            //surname
            Label {
                text: "Surname:";
                color: design.txcolor;
            }
            Text {
                color: design.txcolor
                font.bold: true
                
                text: surname
            }
            
            Button {
                id: "window_offlinebutton";
                text: "Add friend";
                onClicked: {
                    window.addFriend();
                }
                style: DesignButton{}
            }
            Button {
                id: "window_loginbutton";
                text: "Send message";
                onClicked: {
                    //NEEDS PORT
                    //window.doLogin(m_username.text,m_password.text);
                }
                
                style: DesignButton{}
            }
        }
    }
}
