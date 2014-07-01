import QtQuick 2.2
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.1

//gluon player specific imports
import Gluon.Player.Desktop 0.72 as GluonPlayer

import "utils"

Item{
	id: window
	
	anchors.horizontalCenter: parent.horizontalCenter
	anchors.verticalCenter: parent.verticalCenter
	
	anchors.fill:parent
	
	property string message;
	
	//open animation
	NumberAnimation on opacity {
        id: openAnimation
        from: 0
        to: 1
        duration: 175
        
        onRunningChanged: {
            if (openAnimation.running) {
                window.visible = true;
            }
        }
    }
    
    //close animation
    NumberAnimation on opacity {
        id: closeAnimation
        from: 1
        to: 0
        duration: 175
        onRunningChanged: {
            if (closeAnimation.running) {
                window.visible = true;
            } else {
                window.visible = false;
            }
        }
    }
	
	function open(str){
        window.message = str;
		openAnimation.start();
	}
	
	function close(){
		closeAnimation.start();
	}
    
    //black bg rectangle
    Rectangle{
        anchors.fill: parent
        color: "#BB000000"
        
        MouseArea{
            anchors.fill: parent
            
            onClicked:{
                window.close()
            }
        }
    }
    
    GluonModalDialog{
        id : loginFormProxy;
        target: window_mainbox
        space: 20
        
        //here in order to prevent accidental close of modal
        //clicking inside modal but not on buttons
        MouseArea{
            anchors.fill: parent
        }
    }
        
    Column{
        id:window_mainbox
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        
        spacing: 15
        
        Label {
                font.pointSize: 17
                font.family: "Arial"
                anchors.left: window_maincolumn.left
                anchors.right: window_maincolumn.right
                
                anchors.bottomMargin: 10
                
                horizontalAlignment: Text.AlignHCenter
                
                text: window.message;
                color: design.txcolor;
                opacity: 1;
        }
    }
}
