import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents
 
Item {
	
	PlasmaComponents.PageStack {
		id: pageStack
		anchors { top: parent.top; bottom: toolBar.top }
		
		Component.onCompleted:{
			pageStack.push(Qt.createComponent("loginscreen.qml"))
		}
	}
}
