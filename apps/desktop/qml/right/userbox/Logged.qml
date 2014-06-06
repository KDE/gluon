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
            text: "Hello, "+loginscreen.username()+"!"
            font.pointSize: 20
            color: design.txcolor
        }
        Text{
            id: home_userparagraph
            text: "Logged as nickname"
            color: design.txcolor
        }
        
        Button{
            anchors.left: parent.left
            text: "Logout"
            style: DesignButton{}
            onClicked:{
                loginscreen.doLogout()
            }
        }
    }
}