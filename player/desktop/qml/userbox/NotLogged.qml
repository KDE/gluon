 
import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.extras 0.1 as PlasmaExtras
import Gluon.Player.Desktop 0.72 as GluonPlayer

import ".."

Item{
	BackgroundBox{ target: userbox_loggedpage; }

	
	Item{
		id: userbox_loggedpage
		height: childrenRect.height
		width: childrenRect.width
		
		Column{
			width: 200
			spacing: 7
			
			PlasmaExtras.Title{
				id: home_usertitle
				text: "Please Log In!"
				color: "black"
			}
			PlasmaExtras.Paragraph{
				id: home_userparagraph
				text: "You're browsing as anonymous.<br />Please Log In or register a new account."
				color: "black"
			}
			PlasmaComponents.Button{
				anchors.horizontalCenter: parent.horizontalCenter
				text: "Log in"
				onClicked:{
					loginscreen.open()
				}
			}
			PlasmaComponents.Button{
				anchors.horizontalCenter: parent.horizontalCenter
				text: "Register"
				onClicked:{
					registeruserscreen.open()
				}
			}
		}
	}
}
