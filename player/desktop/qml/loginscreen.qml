import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.extras 0.1 as PlasmaExtras
import org.kde.plasma.components 0.1 as PlasmaComponents

Item {
	
     Column {
         anchors.horizontalCenter: parent.horizontalCenter;
         anchors.verticalCenter: parent.verticalCenter;
         
         anchors.right: parent.right;
         anchors.left: parent.left;
         anchors.top: parent.top;
         anchors.bottom: parent.bottom;
         
         anchors.margins: 20;

         spacing: 5;

         PlasmaExtras.Title {
			text: "Gluon Player"
			anchors.horizontalCenter: parent.horizontalCenter;
		 }
         
         Row {
			anchors.right : parent.right;
			anchors.left : parent.left;
			
			PlasmaComponents.Label {
				text: "Username:";
				anchors.left : parent.left;
			}
			PlasmaComponents.TextField {
				anchors.right : parent.right;
			}
		 }
		 Row {
			anchors.right : parent.right;
			anchors.left : parent.left;
			
			PlasmaComponents.Label {
				text: "Password:";
				anchors.left : parent.left;
			}
			PlasmaComponents.TextField {
				anchors.right : parent.right;
			}
		 }
		 
		 PlasmaComponents.Label{
			anchors.right: parent.right
			text: "Have you forgot your password?"
			font.pixelSize: 7
		 }
		 
		 PlasmaComponents.Label{
			anchors.right: parent.right
			text: "Still not registered?"
			font.pixelSize: 7
		 }
		 
		 Row {
			anchors.right : parent.right;
			anchors.left : parent.left;
			
			PlasmaComponents.Button {
				objectName: "quitbutton";
				text: "Quit";
				width : 100;
				anchors.left : parent.left;
				onClicked: console.log("send signal to quit?");
			}
			PlasmaComponents.Button {
				objectName: "loginbutton";
				text: "Login";
				width : 100;
				anchors.right : parent.right;
				onClicked: console.log("send signal to log?");
			}
		 }
     }
}
