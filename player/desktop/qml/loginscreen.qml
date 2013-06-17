import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.extras 0.1 as PlasmaExtras
import org.kde.plasma.components 0.1 as PlasmaComponents

Item {

     Column {
         anchors.horizontalCenter: parent.horizontalCenter
         anchors.verticalCenter: parent.verticalCenter

         spacing: 5

         PlasmaExtras.Title { text: "Gluon Game Store" }
         
         Row {
			anchors.right : parent.right;
			anchors.left : parent.left;
			
			PlasmaComponents.Label {
				text: "Login ID:";
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
     }
}
