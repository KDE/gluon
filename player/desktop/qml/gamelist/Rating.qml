import QtQuick 1.0
import org.kde.qtextracomponents 0.1 as QtExtraComponents
import Qt.labs.shaders 1.0

Item{
	id: ratingbar
	
	property int rate;
	
	width: childrenRect.width
	
	Image{
		id: firststar
		source: "../icons/rating.png"
	}
	Image{
		id: secondstar
		anchors.left: firststar.right
		source: "/usr/share/icons/oxygen/22x22/actions/rating.png"
		
		Component.onCompleted:{
			if (ratingbar.rate <20){
				//Qt.createQmlObject("GrayscaleEffect{ target: parent }",secondstar,"dynSnippet1")
				secondstar.source = "../icons/ratinggs.png"
			}
		}
	}
	Image{
		id: thirdstar
		anchors.left: secondstar.right
		source: "/usr/share/icons/oxygen/22x22/actions/rating.png"
		Component.onCompleted:{
			if (ratingbar.rate <40){
				//Qt.createQmlObject("GrayscaleEffect{ target: parent }",thirdstar,"dynSnippet1")
				thirdstar.source = "../icons/ratinggs.png"
			}
		}
	}
	Image{
		id: fourthstar
		anchors.left: thirdstar.right
		source: "/usr/share/icons/oxygen/22x22/actions/rating.png"
		Component.onCompleted:{
			if (ratingbar.rate <60){
				//Qt.createQmlObject("GrayscaleEffect{ target: parent }",fourthstar,"dynSnippet1")
				fourthstar.source = "../icons/ratinggs.png"
			}
		}
	}
	Image{
		id: fifthstar
		anchors.left: fourthstar.right
		source: "/usr/share/icons/oxygen/22x22/actions/rating.png"
		Component.onCompleted:{
			if (ratingbar.rate <80){
				//Qt.createQmlObject("GrayscaleEffect{ target: parent }",fifthstar,"dynSnippet1")
				fifthstar.source = "../icons/ratinggs.png"
			}
		}
	}
}
