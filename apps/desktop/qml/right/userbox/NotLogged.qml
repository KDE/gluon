import QtQuick 2.2
import QtQuick.Controls 1.1

import "../../utils"

Item{
    id: userbox_loggedpage
    
    height: childrenRect.height
    
    Column{
        spacing: 10
        
        height: childrenRect.height
        
        Text{
            id: home_usertitle
            text: "Log In"
            font.pointSize: 20
            color: design.txcolor
        }
        Text{
            id: home_userparagraph
            text: "You're browsing as anonymous.<br />Please Log In or register a new account."
            color: design.txcolor
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
    
    Component.onCompleted:{
        //TODO: refactor
        //manually setting container height
        userbox_bg.height = childrenRect.height +40
    }
}
