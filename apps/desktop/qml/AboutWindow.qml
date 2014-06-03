import QtQuick 2.2
import QtQuick.Window 2.1  // needed for the Window component

import "utils"

Window {
 
    width: 400
    height: 400
    
    title: "About - Gluon Player"
 
    Background {
        
        Box{
            Column{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                anchors.topMargin: 10
                anchors.bottomMargin: 10
                
                spacing: 10
                
                Text {
                    id: title
                    anchors.left: parent.left
                    anchors.right: parent.right
                    horizontalAlignment: Text.AlignHCenter
                    
                    text: "Gluon Player Desktop (qt5)"
                    
                    font.pointSize: 17
                    font.family: "Arial"
                    
                    color: design.txcolor
                }
                
                Image {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    
                    fillMode: Image.PreserveAspectFit
                    source: "resources/icon.png"
                }
                
                Line{ }
                
                Text {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    horizontalAlignment: Text.AlignHCenter
                    
                    text: "Claudio Desideri (happy.snizzo@gmail.com)\nmore to come..."
                    
                    font.pointSize: 9
                    font.family: "Helvetica"
                    
                    color: design.txcolor
                }
            }
        }
    }
}
