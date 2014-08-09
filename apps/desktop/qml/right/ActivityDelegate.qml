import QtQuick 2.2
import QtQuick.Controls 1.1


import Gluon.Player.Desktop 0.72 as GluonPlayer
import "../utils"


Item{
    id: singleuserdelegate
    anchors.left: parent.left
    anchors.leftMargin: 20
    anchors.right: parent.right
    anchors.rightMargin: 20
    
    height: 17
    width: parent.width
    
    Text{
        id:text
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        
        wrapMode: Text.WordWrap;
        
        color: design.txcolor
        
        font.pointSize: 10
        
        text: message
    }
    
} 
