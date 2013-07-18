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
				text: "Hello, "+home_userbox.firstname()+"!"
				color: "black"
			}
			PlasmaExtras.Paragraph{
				id: home_userparagraph
				text: "Logged as "+home_userbox.username()
				color: "black"
			}
			PlasmaComponents.Button{
				anchors.horizontalCenter: parent.horizontalCenter
				text: "Logout"
				onClicked:{
					home_userbox.logout()
				}
			}
		}
	}
}