 
import QtQuick 2.2

Item{
    id: ratingbar
    
    property int rate;
    
    width: childrenRect.width
    
    Image{
        id: firststar
        source: "../../resources/rating.png"
    }
    Image{
        id: secondstar
        anchors.left: firststar.right
        source: "../../resources/rating.png"
        
        Component.onCompleted:{
            if (ratingbar.rate <20){
                //Qt.createQmlObject("GrayscaleEffect{ target: parent }",secondstar,"dynSnippet1")
                secondstar.source = "../../resources/ratinggs.png"
            }
        }
    }
    Image{
        id: thirdstar
        anchors.left: secondstar.right
        source: "../../resources/rating.png"
        Component.onCompleted:{
            if (ratingbar.rate <40){
                //Qt.createQmlObject("GrayscaleEffect{ target: parent }",thirdstar,"dynSnippet1")
                thirdstar.source = "../../resources/ratinggs.png"
            }
        }
    }
    Image{
        id: fourthstar
        anchors.left: thirdstar.right
        source: "../../resources/rating.png"
        Component.onCompleted:{
            if (ratingbar.rate <60){
                //Qt.createQmlObject("GrayscaleEffect{ target: parent }",fourthstar,"dynSnippet1")
                fourthstar.source = "../../resources/ratinggs.png"
            }
        }
    }
    Image{
        id: fifthstar
        anchors.left: fourthstar.right
        source: "../../resources/rating.png"
        Component.onCompleted:{
            if (ratingbar.rate <80){
                //Qt.createQmlObject("GrayscaleEffect{ target: parent }",fifthstar,"dynSnippet1")
                fifthstar.source = "../../resources/ratinggs.png"
            }
        }
    }
}