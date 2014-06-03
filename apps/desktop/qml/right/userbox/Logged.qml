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
// 				TODO: fixme
// 				text: "Hello, "+home_userbox.firstname()+"!"
            text: "Hello, loggeduser!"
            font.pointSize: 20
            color: design.txcolor
        }
        Text{
            id: home_userparagraph
            text: "Logged as nickname"
            color: design.txcolor
        }
        
        Button{
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Logout"
            style: DesignButton{}
// 				onClicked:{
// 					home_userbox.logout()
// 				}
        }
    }
}