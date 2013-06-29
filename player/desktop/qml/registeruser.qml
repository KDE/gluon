import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.extras 0.1 as PlasmaExtras
import org.kde.plasma.components 0.1 as PlasmaComponents
import Gluon.Player.Desktop 0.72 as GluonPlayer
 
Item {
	
	Rectangle {
		id: background
		anchors.fill: parent;
		Image { source: "bg.png"; fillMode: Image.Tile; anchors.fill: parent;  opacity: 1 }
	}
	
	GluonPlayer.RegisterUserForm{
		id: registerUserFormProxy;
		onRegistrationProcessCompleted:{
			register_outputlabel.text = "<b>"+message+"</b>";
		}
	}
	
	Column {
		
		width: 300;
		
		anchors.horizontalCenter: parent.horizontalCenter;
		anchors.verticalCenter: parent.verticalCenter;

		anchors.top: parent.top;
		anchors.bottom: parent.bottom;

		anchors.margins: 20;

		spacing: 5;
		
		PlasmaExtras.Title {
			text: "Sign up!"
			anchors.horizontalCenter: parent.horizontalCenter;
		}
		
		PlasmaExtras.Paragraph {
			text: "Through this wizard you'll register a new account on the GamingFreedom network. <br>This account will work either for Gluon Creator, Gluon Player, www.gamingfreedom.org and any Gluon affiliate."
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
				id: register_login;
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
				id: register_password;
				anchors.right : parent.right;
			}
		}
		Row {
			anchors.right : parent.right;
			anchors.left : parent.left;

			PlasmaComponents.Label {
				text: "";
				anchors.left : parent.left;
			}
			PlasmaComponents.TextField {
				id: register_password2;
				anchors.right : parent.right;
			}
		}
		Row {
			anchors.right : parent.right;
			anchors.left : parent.left;

			PlasmaComponents.Label {
				text: "First name:";
				anchors.left : parent.left;
			}
			PlasmaComponents.TextField {
				id: register_firstname;
				anchors.right : parent.right;
			}
		}
		Row {
			anchors.right : parent.right;
			anchors.left : parent.left;

			PlasmaComponents.Label {
				text: "Last name:";
				anchors.left : parent.left;
			}
			PlasmaComponents.TextField {
				id: register_lastname;
				anchors.right : parent.right;
			}
		}
		Row {
			anchors.right : parent.right;
			anchors.left : parent.left;

			PlasmaComponents.Label {
				text: "E-mail:";
				anchors.left : parent.left;
			}
			PlasmaComponents.TextField {
				id: register_email;
				anchors.right : parent.right;
			}
		}
		
		PlasmaComponents.Label {
			id: register_outputlabel;
			text: "";
		}
		
		Row {
			anchors.right : parent.right;
			anchors.left : parent.left;

			PlasmaComponents.Button {
				text: "Cancel";
				width : 100;
				anchors.left : parent.left;
				onClicked: pageStack.pop();
			}
			PlasmaComponents.Button {
				text: "Send";
				width : 100;
				anchors.right : parent.right;
				onClicked: registerUserFormProxy.addUser(register_login.text, register_password.text, register_password2.text, register_firstname.text, register_lastname.text, register_email.text);
			}
		}
	}
}
