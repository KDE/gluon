import QtQuick 1.0

Item{
	width: parent.width
	height: 100
	
	XmlListModel {
		id: highlightsModel
		source: "http://www.gamingfreedom.org/highlights.php"
		query: "/xml/highlight/item"

		XmlRole { name: "title"; query: "title/string()" }
		XmlRole { name: "image"; query: "image/string()" }
		XmlRole { name: "description"; query: "description/string()" }
	}
	
	ListView {
		width: parent.width; height: parent.height
		model: highlightsModel
		delegate: Text { text: title + ": " + image }
	}
	
}
