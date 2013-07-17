import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.extras 0.1 as PlasmaExtras
import org.kde.plasma.components 0.1 as PlasmaComponents
import Gluon.Player.Desktop 0.72 as GluonPlayer

Item {
	id: loginScreen
	visible: false
	
	anchors.fill: parent;
	
	function open(){
		this.visible = true
	}
	
	function close(){
		this.visible = false
	}
	
	Rectangle{
		anchors.fill: parent;
		color: "black";
		opacity: 0.6;
	}
	
	Item {
		anchors.horizontalCenter: parent.horizontalCenter;
		
		anchors.top: parent.top;
		anchors.bottom: parent.bottom;
		
		GluonPlayer.LoginForm{
			id : loginFormProxy;
			onLoginCompleted: {
				loginScreen.visible = false
			}
			onLoginFail: {
				login_outputlabel.text = "<b>Login failed!</b>";
			}
			
			BackgroundBox {
				target: loginscreen_maincolumn;
			}
			
			anchors.horizontalCenter: parent.horizontalCenter;
			
			anchors.top: parent.top;
			anchors.bottom: parent.bottom;
			
			Column {
				id: loginscreen_maincolumn;
				width: 300;
				anchors.horizontalCenter: parent.horizontalCenter;
				anchors.verticalCenter: parent.verticalCenter;
				spacing: 5;
				
				PlasmaExtras.Title {
					text: "Gluon Player";
					color: "black";
					anchors.horizontalCenter: parent.horizontalCenter;
					opacity: 1;
				}
				Row {
					anchors.right : parent.right;
					anchors.left : parent.left;

					PlasmaComponents.Label {
						text: "Username:";
						anchors.left : parent.left;
						color: "black";
					}
					PlasmaComponents.TextField {
						id: m_username;
						anchors.right : parent.right;
						KeyNavigation.tab: m_password;
					}
				}
				Row {
					anchors.right : parent.right;
					anchors.left : parent.left;

					PlasmaComponents.Label {
						text: "Password:";
						anchors.left : parent.left;
						color: "black";
					}
					PlasmaComponents.TextField {
						echoMode: TextInput.Password 
						id: m_password;
						anchors.right : parent.right;
						KeyNavigation.tab: m_username;
						Keys.onReturnPressed: loginFormProxy.doLogin(m_username.text,m_password.text);
					}
				}

				PlasmaComponents.Label{
					anchors.right: parent.right;
					color: "blue";
					text: "Recover your password";
					font.pixelSize: 7;
					MouseArea{
						anchors.fill: parent
						onClicked: print("TODO: implement recover password on qml/loginscreen.qml");
					}
				}

				PlasmaComponents.Label{
					color: "blue";
					anchors.right: parent.right
					text: "Register an account";
					font.pixelSize: 7
					MouseArea{
						anchors.fill: parent
						onClicked: pageStack.push(Qt.createComponent("registeruser.qml"))
					}
				}
				
				PlasmaComponents.Label {
					id: login_outputlabel;
					text: "";
					color: "black";
				}
				
				Row {
					anchors.right : parent.right;
					anchors.left : parent.left;
					anchors.bottomMargin: 10;

					PlasmaComponents.Button {
						objectName: "loginscreen_offlinebutton";
						text: "Play Offline";
						width : 100;
						anchors.left : parent.left;
						onClicked: {
							loginScreen.visible = false;
						}
					}
					PlasmaComponents.Button {
						objectName: "loginscreen_loginbutton";
						text: "Login";
						width : 100;
						anchors.right : parent.right;
						onClicked: {
							loginFormProxy.doLogin(m_username.text,m_password.text);
							
						}
					}
				}
			}
		}
	}
}
