import QtQuick 2.1
import QtQuick.Controls 1.1

import ".."

MenuBar {
    Menu {
        title: qsTr("File")
	MenuItem {
            text: qsTr("Open")
            onTriggered: Qt.quit();
        }
	MenuSeparator { }
        MenuItem {
            text: qsTr("Exit")
            onTriggered: Qt.quit();
        }
    }
    
    Menu {
        title: qsTr("Settings")
        MenuItem {
            text: qsTr("Account")
            onTriggered: Qt.quit();
        }
    }
    
    Menu {
        title: qsTr("Chat")
        MenuItem {
            text: qsTr("Open Chat")
            onTriggered:{
                var component = Qt.createComponent("../chat/ChatWindow.qml");
                var win = component.createObject(mainWindow);
                win.show();
            }
        }
    }
    
    Menu {
        title: qsTr("Help")
        MenuItem {
            text: qsTr("Handbook")
            onTriggered: Qt.quit();
        }
        MenuSeparator { }
        MenuItem {
            text: qsTr("About KDE")
            onTriggered: Qt.quit();
        }
        MenuItem {
            text: qsTr("About Gluon Player")
            onTriggered:{
                var component = Qt.createComponent("../AboutWindow.qml");
                var win = component.createObject(mainWindow);
                win.show();
            }
        }
    }
}
