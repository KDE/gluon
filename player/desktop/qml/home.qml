import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.extras 0.1 as PlasmaExtras
import Gluon.Player.Desktop 0.72 as GluonPlayer


Item {
	
	Background { }
		
	Rectangle {
		anchors.right: centralBox.left;
		anchors.top: centralBox.top;
		anchors.rightMargin: 40;
		
		width: 100
		
		BackgroundBox{ target: home_leftcolumn; }
		
		Column{
			id: home_leftcolumn
			width: 100
			
			spacing: 10
			
			PlasmaComponents.Button{
				height: 100
				iconSource: "download.svg"
			}
			
			PlasmaComponents.Button{
				height: 100
				iconSource: "media-playback-start.svg"
			}
			
			PlasmaComponents.Button{
				height: 100
				iconSource: "im-user.svg"
			}
		}
		
	}
		

	Rectangle {
		id: centralBox;
		
		anchors.horizontalCenter: parent.horizontalCenter;
		anchors.top: parent.top;
		anchors.topMargin: 20;
		
		width: 500
		
		BackgroundBox{ target: home_centralbox; }
		
		Column{
				id: home_centralbox
				width: 500
				
				PlasmaExtras.Title{
					text: "loading..."
					color: "black"
				}
				PlasmaComponents.Label{
					text: "loading..."
					color: "black"
				}
		}
	}
			
	Rectangle {
		id: rightColumn;
		
		anchors.left: centralBox.right;
		anchors.top: centralBox.top;
		anchors.leftMargin: 40;
		
		width: 200
		
		BackgroundBox{ target: home_rightcolumn; }
			
		GluonPlayer.UserBox{
			id: home_userbox;
			property alias title: home_usertitle.text;
			property alias label: home_userlabel.text;
			
			
			onDataLoaded: {
				title = "Hello, "+home_userbox.firstname()+"!"
				label = "Logged as "+home_userbox.username();
			}
			
			Column{
				id: home_rightcolumn
				width: 200
			
				PlasmaExtras.Title{
					id: home_usertitle
					text: "loading..."
					color: "black"
				}
				PlasmaComponents.Label{
					id: home_userlabel
					text: "loading..."
					color: "black"
				}
			}
		}
	}
}
