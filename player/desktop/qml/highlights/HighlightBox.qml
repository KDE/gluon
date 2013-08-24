import QtQuick 1.0

Item{
	id: highlightBoxId
	width: parent.width
	height: 360
	
	PathView {
		id: view
		width: parent.width
		height: 360
		pathItemCount: 1
		preferredHighlightBegin: 0
		preferredHighlightEnd: 0
		highlightRangeMode: PathView.StrictlyEnforceRange
		interactive:false
		
		model: highlightsModel
		delegate: HighlightItem { }
		path: Path {
			startX: highlightBoxId.width / 2
			startY: highlightBoxId.height / 2
			PathLine { y: highlightBoxId.height / 2; x: (highlightBoxId.x /2) +1; }
		}
	}
	
	Timer {
        interval: 6500; running: true; repeat: true;
        onTriggered: view.incrementCurrentIndex();
    }
	
	XmlListModel {
		id: highlightsModel
		source: "http://www.gamingfreedom.org/highlights.php"
		query: "/xml/highlight/item"

		XmlRole { name: "title"; query: "title/string()" }
		XmlRole { name: "image"; query: "image/string()" }
		XmlRole { name: "description"; query: "description/string()" }
	}
	
}
