import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.extras 0.1 as PlasmaExtras
import Gluon.Player.Desktop 0.72 as GluonPlayer
 
Item {
	
	Rectangle {
		id: background
		anchors.fill: parent;
		Image { source: "bg.png"; fillMode: Image.Tile; anchors.fill: parent;  opacity: 1 }
	}
	
	Row {
		anchors.horizontalCenter: parent.horizontalCenter;
		
		anchors.topMargin: 20;
		anchors.top: parent.top;
		anchors.bottom: parent.bottom;
		spacing: 20;
		
		Column {
			anchors.topMargin: 20;
			Rectangle {
				width: 150;
				height: 200;
				color: "red";
				Text {
					text: "MENU";
				}
			}
		}
		
		Column {
			Rectangle {
				width: 500;
				height: 100;
				color: "green";
				Text {
					text: "CONTENT";
				}
			}
		}
		
		Column {
			Rectangle {
				width: 200;
				height: 100;
				color: "blue";
				Text {
					text: "SOCIAL";
				}
			}
			
			GluonPlayer.UserBox {
				
			}
		}
	}
}
