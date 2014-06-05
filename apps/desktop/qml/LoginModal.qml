import QtQuick 2.2
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.1

//gluon player specific imports
import Gluon.Player.Desktop 0.72 as GluonPlayer

import "utils"

GluonPlayer.LoginForm{
	id: loginScreen
	
	anchors.horizontalCenter: parent.horizontalCenter
	anchors.verticalCenter: parent.verticalCenter
	
	anchors.fill:parent
	
	//open animation
	NumberAnimation on opacity {
        id: openAnimation
        from: 0
        to: 1
        duration: 175
        
        onRunningChanged: {
            if (openAnimation.running) {
                loginScreen.visible = true;
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
                loginScreen.visible = true;
            } else {
                loginScreen.visible = false;
            }
        }
    }
	
	function open(){
		openAnimation.start();
        
        console.log("open loginscreen started");
	}
	
	function close(){
		closeAnimation.start();
        console.log("close loginscreen started");
	}
	
    //result handle
    onLoginCompleted: {
        loginScreen.close();
        console.log("LoginModal.qml: login succeeded");
    }
    onLoginFail: {
        login_outputlabel.text = "<b>Login failed!</b>";
        console.log("LoginModal.qml: login failed");
    }
    
    //black bg rectangle
    Rectangle{
        anchors.fill: parent
        color: "#BB000000"
        
        MouseArea{
            anchors.fill: parent
            
            onClicked:{
                loginScreen.close()
            }
        }
    }
    
    GluonModalDialog{
        id : loginFormProxy;
        target: loginscreen_mainbox
        space: 20
    }
        
    Column{
        id:loginscreen_mainbox
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        
        spacing: 15
        
        Label {
                font.pointSize: 27
                font.family: "Arial"
                anchors.left: loginscreen_maincolumn.left
                anchors.right: loginscreen_maincolumn.right
                
                anchors.bottomMargin: 10
                
                horizontalAlignment: Text.AlignHCenter
                
                text: "Gluon Player";
                color: design.txcolor;
                opacity: 1;
        }
        
        Grid {
            id: loginscreen_maincolumn;
            
            columns: 2
            spacing: 10
            
            Label {
                text: "Username:";
                color: design.txcolor;
                
                verticalAlignment: Text.AlignVCenter
            }
            TextField {
                id: m_username;
                KeyNavigation.tab: m_password;
                
                style: DesignTextField{}
            }
            Label {
                text: "Password:";
                color: design.txcolor;
            }
            TextField {
                echoMode: TextInput.Password 
                id: m_password;
                KeyNavigation.tab: m_username;
                
                style: DesignTextField{}
                
                //NEEDS PORT
                Keys.onReturnPressed: loginScreen.doLogin(m_username.text,m_password.text);
            }

            Text{
                color: design.txlkcolor;
                text: "Recover your password";
                font.pixelSize: 7;
                MouseArea{
                    anchors.fill: parent
                    onClicked: print("TODO: implement recover password on LoginModal.qml");
                }
            }
            Item{}

            Text{
                color: design.txlkcolor;
                text: "Register an account";
                font.pixelSize: 7
                MouseArea{
                    anchors.fill: parent
                    
                    // NEEDS PORT
                    onClicked: {
                        loginScreen.close();
                        registerUserScreen.open();
                    }
                }
            }
            Item{}
            
            Text {
                id: login_outputlabel;
                text: "";
                color: "black";
            }
            Item{}
            
            Button {
                id: "loginscreen_offlinebutton";
                text: "Play Offline";
                onClicked: {
                    closeAnimation.start();
                }
                style: DesignButton{}
            }
            Button {
                id: "loginscreen_loginbutton";
                text: "Login";
                onClicked: {
                    //NEEDS PORT
                    loginScreen.doLogin(m_username.text,m_password.text);
                }
                
                style: DesignButton{}
            }
        }
    }
}
