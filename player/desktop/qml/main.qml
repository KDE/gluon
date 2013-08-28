import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.extras 0.1 as PlasmaExtras
import Gluon.Player.Desktop 0.72 as GluonPlayer

Item {
	id: gluonplayerid
	
	Background { }
		
	LoginScreen{ 
		id: loginscreen
		z: 10 
	}
	
	RegisterUser{
		id: registeruserscreen
		z: 10
	}
	
		
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
				onClicked: { centralBox.showDownloadableGames(); }
			}
			
			PlasmaComponents.Button{
				height: 100
				iconSource: "media-playback-start.svg"
				onClicked: { centralBox.showInstalledGames(); }
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
		anchors.horizontalCenterOffset: -50;
		anchors.top: parent.top;
		anchors.topMargin: 20;
		anchors.bottom: parent.bottom;
		
		color: "transparent";
		
		width: 550
		
		function showInstalledGames(){
			central_stack.pop(true,true);
			central_stack.push(Qt.createComponent("gamelist/InstalledList.qml"),"",true);
		}
		
		function showDownloadableGames(){
			central_stack.pop(true,true);
			central_stack.push(Qt.createComponent("gamelist/DownloadableList.qml"),"",true);
		}
		
		PlasmaComponents.PageStack{
			id: central_stack;
			width: 550
		
			Component.onCompleted:{
				central_stack.push(Qt.createComponent("gamelist/DownloadableList.qml"),"",true);
			}
		}
	}
	
	Rectangle {
		id: rightColumn;
		
		anchors.left: centralBox.right;
		anchors.top: centralBox.top;
		anchors.leftMargin: 40;
		
		width: 200
			
		GluonPlayer.UserBox{
			id: home_userbox;
			
			onNeedsAuthentication: {
				loginscreen.open(true,true);
			}
			
			onDataLoaded: {
				userbox_stack.pop()
				userbox_stack.push(Qt.createComponent("userbox/Logged.qml"),"",true)
			}
			
			onLogoutFinished: {
				userbox_stack.pop(true,true)
				userbox_stack.push(Qt.createComponent("userbox/NotLogged.qml"),"",true)
			}
			
			Column{
				id: home_rightcolumn
				width: 200
				
				height: childrenRect.height
				
				PlasmaComponents.PageStack{
					id: userbox_stack;
				
					Component.onCompleted:{
						userbox_stack.push(Qt.createComponent("userbox/NotLogged.qml"),"",true)
					}
				}
			}
		}
	}
}