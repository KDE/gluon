import QtQuick 2.2
import QtQuick.Controls 1.1

import "../../utils"

Item{
    id: userbox_loggedpage
    
    height: childrenRect.height
    
    function doLogout(){
        xmppClient.logout();
        self.doLogout();
    }
    
    Column{
        spacing: 10
        
        height: childrenRect.height
        
        Text{
            id: home_usertitle
            text: "Hello, "+self.username+"!"
            font.pointSize: 20
            color: design.txcolor
        }
        
        Button{
            anchors.left: parent.left
            text: "Logout"
            style: DesignButton{}
            onClicked:{
                userbox_loggedpage.doLogout();
            }
        }
    }
}