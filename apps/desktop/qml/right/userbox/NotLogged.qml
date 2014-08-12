import QtQuick 2.2
import QtQuick.Controls 1.1

import "../../utils"

Item{
    id: userbox_loggedpage
    
    anchors.fill: parent

    Text{
        id: home_usertitle
        
        anchors.top: parent.top
        anchors.left: parent.left
        
        font.pixelSize: 20
        font.bold: true
        
        text: "Account"
        
        color: design.txcolor
    }
    Text{
        id: home_userparagraph
        
        anchors.top: home_usertitle.bottom
        anchors.topMargin: 10
        
        width: parent.width
        
        text: "You're browsing as anonymous.<br />Please Log In or register a new account."
        
        font.pixelSize: 15
        
        wrapMode: Text.WordWrap
        
        color: design.txcolor
    }
    
    Item{
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        
        anchors.horizontalCenter: parent.horizontalCenter
        
        width: childrenRect.width
        height: childrenRect.height
        
        Button{
            id: loginbutton
            text: "Log in"
            style: DesignButton{}
            onClicked: loginscreen.open()
        }
        Button{
            id: registerbutton
            
            anchors.left: loginbutton.right
            anchors.leftMargin: 10
            
            text: "Register"
            style: DesignButton{}
            onClicked: registeruserscreen.open()
        }
    }
}
