import QtQuick 2.2
import QtQuick.Controls 1.1

import "../../utils"

Item{
    id: userbox_loggedpage
    anchors.left:parent.left
    anchors.right:parent.right
    anchors.leftMargin:  20
    anchors.rightMargin: 20
    
    Column{
        spacing: 10
        
        Text{
            id: home_usertitle
            text: "Please Log In!"
            color: "black"
        }
        Text{
            id: home_userparagraph
            text: "You're browsing as anonymous.<br />Please Log In or register a new account."
            color: "black"
        }
        Row{
            spacing: 10
            Button{ 
                text: "Log in"
                style: DesignButton{}
                onClicked:{
                    loginscreen.open()
                }
            }
            Button{
                text: "Register"
                style: DesignButton{}
                onClicked:{
                    registeruserscreen.open()
                }
            }
        }
    }
}
