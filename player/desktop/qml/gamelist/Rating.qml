import QtQuick 1.0
import org.kde.qtextracomponents 0.1 as QtExtraComponents
import Qt.labs.shaders 1.0

Item{
	id: ratingbar
	property int rate;
	Image{
		id: firststar
		source: "/usr/share/icons/oxygen/22x22/actions/rating.png"
	}
	Image{
		id: secondstar
		anchors.right: firststar.left
		source: "/usr/share/icons/oxygen/22x22/actions/rating.png"
		
		Component.onCompleted:{
			if (ratingbar.rate <20){
				Qt.createQmlObject("GrayscaleEffect{ target: parent }",secondstar,"dynSnippet1")
			}
		}
	}
	Image{
		id: thirdstar
		anchors.right: secondstar.left
		source: "/usr/share/icons/oxygen/22x22/actions/rating.png"
		Component.onCompleted:{
			if (ratingbar.rate <40){
				Qt.createQmlObject("GrayscaleEffect{ target: parent }",thirdstar,"dynSnippet1")
			}
		}
	}
	Image{
		id: fourthstar
		anchors.right: thirdstar.left
		source: "/usr/share/icons/oxygen/22x22/actions/rating.png"
		Component.onCompleted:{
			if (ratingbar.rate <60){
				Qt.createQmlObject("GrayscaleEffect{ target: parent }",fourthstar,"dynSnippet1")
			}
		}
	}
	Image{
		id: fifthstar
		anchors.right: fourthstar.left
		source: "/usr/share/icons/oxygen/22x22/actions/rating.png"
		Component.onCompleted:{
			if (ratingbar.rate <80){
				Qt.createQmlObject("GrayscaleEffect{ target: parent }",fifthstar,"dynSnippet1")
			}
		}
	}
}
