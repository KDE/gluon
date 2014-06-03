import QtQuick 2.2
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0

import "../../utils"

Item{
	width: parent.width -20
	height: parent.height -20
	
	BusyIndicator{
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		running: true
	}
	
	Image{
		id: highImage
		source: image
		width: parent.width
		height: parent.height
	}
	
	Item {
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		
		Rectangle{
			anchors.left: highlightItemSummaryId.left
			anchors.top: highlightItemTitleId.top
			anchors.bottom: highlightItemSummaryId.bottom
			anchors.right: parent.right
			color: "white"
			opacity: 0.5
		}
		
		Text{
			id: highlightItemTitleId
			anchors.left: highlightItemSummaryId.left
			anchors.leftMargin: 10
			anchors.bottom: highlightItemSummaryId.top
			anchors.bottomMargin: 5
			font.pointSize: 25
            color: "black"
			text: title
			font.family: "Arial"
            wrapMode: Text.WordWrap
		}
		
		Glow {
            radius: 8
            samples: 16
            color: "white"
            source: highlightItemTitleId
            anchors.fill: highlightItemTitleId
        }
		
		Text{
			id: highlightItemSummaryId
			anchors.right: parent.right
			anchors.rightMargin: 10
			anchors.left: parent.left
			anchors.bottom: parent.bottom
			text: description
			wrapMode: Text.WordWrap
		}
	}
}