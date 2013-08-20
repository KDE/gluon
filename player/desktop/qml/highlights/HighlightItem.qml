import QtQuick 1.0
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.extras 0.1 as PlasmaExtras
import ".."

Item{
	width: parent.width
	height: parent.height
	
	PlasmaComponents.ProgressBar{
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		value: highImage.progress
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
		
		PlasmaExtras.Title{
			id: highlightItemTitleId
			anchors.left: highlightItemSummaryId.left
			anchors.bottom: highlightItemSummaryId.top
			text: title
		}
		
		PlasmaExtras.Paragraph{
			id: highlightItemSummaryId
			anchors.right: parent.right
			anchors.rightMargin: 10
			anchors.left: parent.left
			anchors.bottom: parent.bottom
			text: description
		}
	}
}