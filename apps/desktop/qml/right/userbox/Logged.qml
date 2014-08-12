import QtQuick 2.2
import QtQuick.Controls 1.1

import "../../utils"

Item{
    id: userbox_loggedpage
    
    anchors.fill: parent
    
    function doLogout(){
        xmppClient.logout();
        self.doLogout();
    }
        
    Text{
        id: home_usertitle
        
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        
        text: self.username
        font.pixelSize: 20
        font.bold: true
        color: design.txcolor
    }
    
    Button{
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        
        anchors.rightMargin: 20
        
        text: "Logout"
        style: DesignButton{}
        onClicked:{
            userbox_loggedpage.doLogout();
        }
    }
}