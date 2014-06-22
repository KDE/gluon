import QtQuick 2.2
import Gluon.Player.Desktop 0.72 as GluonPlayer
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0

import "../../utils"
import "../gamelist"

Flickable{
    id: socialView
    contentWidth: parent.width
    contentHeight: socialBox.height + 40  //20 pixels margin top + 20 margin bottom
    flickableDirection: Flickable.VerticalFlick
    clip: false
    boundsBehavior: Flickable.StopAtBounds
    
    anchors.left: parent.left;
    anchors.right: parent.right;

    width: parent.width;
    
    property string gameId;    
    
    Box {
        anchors.fill: parent
        Column{
            id:socialBox
            anchors.left:parent.left
            anchors.right:parent.right
            anchors.leftMargin:20
            anchors.rightMargin:20
            anchors.top: parent.top
            anchors.topMargin: 20
            spacing: 10
            Item{
                width:parent.width
                height: childrenRect.height
                
                Heading{
                    id: searchFriendHeading
                    level: 2
                    text: "Search a friend"
                }
                
                TextField{
                    anchors.top:searchFriendButton.top
                    anchors.left: parent.left
                    anchors.right: searchFriendButton.left
                    anchors.rightMargin: 10
                    style: DesignTextField{}
                }
                
                Button{
                    id:searchFriendButton
                    anchors.top:searchFriendHeading.bottom
                    anchors.topMargin: 10
                    anchors.right:parent.right
                    text: "search"
                    style: DesignButton{}
                }
                
            }
            
            Line{}
            
            Text{
                color: design.txcolor
                text: "No user found."
            }
        }
        
    }
} 
