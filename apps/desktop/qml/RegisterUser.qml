import QtQuick 2.2
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.1

import "utils"
 
Item {
	id: registerUserScreen
	
	anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
	
	anchors.fill: parent;
	
    //open animation
    NumberAnimation on opacity {
        id: openAnimation
        from: 0
        to: 1
        duration: 175
        
        onRunningChanged: {
            if (openAnimation.running) {
                registerUserScreen.visible = true;
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
                registerUserScreen.visible = true;
            } else {
                registerUserScreen.visible = false;
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
    
    /*
     * clean all form fields' value
     */
    function cleanFields()
    {
        register_login.text = "";
        register_email.text = "";
        register_firstname.text = "";
        register_lastname.text = "";
        register_password.text = "";
        register_password2.text = "";
    }
    
    function registrationProcessCompleted(hint){
        if(hint!="Registration succeeded."){
            register_outputlabel.text = hint;
        } else {
            register_outputlabel.text = "";
            cleanFields();
            close();
            notification.open(hint);
        }
    }
    
    function register(){
        self.addUser(register_login.text, register_password.text, register_password2.text, register_firstname.text, register_lastname.text, register_email.text);
        xmppClient.createAccount(register_firstname.text + " " + register_lastname.text, register_login.text, register_email.text, register_password2.text); //createAccount(QString name, QString username, QString email, QString password)
    }
    
    Component.onCompleted:{
        self.onRegistrationProcessCompleted.connect(registrationProcessCompleted);
    }
    
    //black bg rectangle
    Rectangle{
        anchors.fill: parent
        color: "#BB000000"
        
        MouseArea{
            anchors.fill: parent
            
            onClicked:{
                registerUserScreen.close()
            }
        }
    }
    
    GluonModalDialog{
        id : loginFormProxy;
        target: registeruser_maincolumn
        space: 20
        
        //here in order to prevent accidental close of modal
        //clicking inside modal but not on buttons
        MouseArea{
            anchors.fill: parent
        }
    }
        
    Column {
        id: registeruser_maincolumn;
        
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        
        spacing: 15
        
        Text {
            text: "Sign up!"
            anchors.horizontalCenter: parent.horizontalCenter;
            color: design.txcolor;
            
            font.pointSize: 20
        }
        
        Text{
            width: 300
            
            text: "<b>Create a new Gluon account:</b><br><i>(this will work on gamingfreedom.org, Gluon Player, Gluon Creator and any Gluon affiliate)</i>"
            anchors.horizontalCenter: parent.horizontalCenter;
            color: design.txcolor;
            
            wrapMode: Text.WordWrap
        }
        
        Item {
            anchors.right : parent.right;
            anchors.left : parent.left;
            
            height: childrenRect.height
            
            Label {
                text: "Username:";
                anchors.left : parent.left;
                color: design.txcolor;
            }
            TextField {
                id: register_login;
                anchors.right : parent.right;
                KeyNavigation.tab: register_password;
                
                style: DesignTextField{}
            }
        }
        Item {
            anchors.right : parent.right;
            anchors.left : parent.left;
            
            height: childrenRect.height
            
            Label {
                text: "Password:";
                anchors.left : parent.left;
                color: design.txcolor;
            }
            TextField {
                echoMode: TextInput.Password;
                id: register_password;
                anchors.right : parent.right;
                KeyNavigation.tab: register_password2;
                style: DesignTextField{}
            }
        }
        Item {
            anchors.right : parent.right;
            anchors.left : parent.left;
            
            height: childrenRect.height
            
            Label {
                text: "";
                anchors.left : parent.left;
                color: design.txcolor;
            }
            TextField {
                echoMode: TextInput.Password;
                id: register_password2;
                anchors.right : parent.right;
                KeyNavigation.tab: register_firstname;
                style: DesignTextField{}
            }
        }
        Item {
            anchors.right : parent.right;
            anchors.left : parent.left;
            
            height: childrenRect.height
            
            Label {
                text: "First name:";
                anchors.left : parent.left;
                color: design.txcolor;
            }
            TextField {
                id: register_firstname;
                anchors.right : parent.right;
                KeyNavigation.tab: register_lastname;
                style: DesignTextField{}
            }
        }
        Item {
            anchors.right : parent.right;
            anchors.left : parent.left;
            
            height: childrenRect.height
            
            Label {
                text: "Last name:";
                anchors.left : parent.left;
                color: design.txcolor;
            }
            TextField {
                id: register_lastname;
                anchors.right : parent.right;
                KeyNavigation.tab: register_email;
                style: DesignTextField{}
            }
        }
        Item {
            anchors.right : parent.right;
            anchors.left : parent.left;
            
            height: childrenRect.height
            
            Label {
                text: "E-mail:";
                anchors.left : parent.left;
                color: design.txcolor;
            }
            TextField {
                id: register_email;
                anchors.right : parent.right;
                KeyNavigation.tab: register_login;
                style: DesignTextField{}
                Keys.onReturnPressed: register();
            }
        }
        
        Label {
            anchors.left: parent.left
            anchors.right: parent.right
            id: register_outputlabel;
            text: "";
            
            color: design.warning;
            
            horizontalAlignment: Text.AlignHCenter;
            
            font.bold: true;
        }
        
        Item {
            anchors.right : parent.right;
            anchors.left : parent.left;
            
            height: childrenRect.height
            
            Button {
                text: "Login Now";
                anchors.left : parent.left;
                onClicked: {
                    registeruserscreen.close();
                    loginscreen.open();
                }
                style: DesignButton{}
            }
            Button {
                text: "Send";
                style: DesignButton{}
                anchors.right : parent.right;
                onClicked: register();
            }
        }
    }
}
