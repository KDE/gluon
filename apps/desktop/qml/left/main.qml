import QtQuick 2.2
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0

import "../utils"

Box{
    anchors.fill: parent
    
    Column{
        id: home_leftcolumn
        
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        
        anchors.topMargin: 20
        
        spacing: 10
        
        Rectangle{
            color: design.bgdarkcolor
            height: 64
            width: 64
            Image{
                id: homeimage
                anchors.fill: parent
                source: "../resources/home_64.png"
                //style: DesignButton{}
                //onClicked: { centralBox.showDownloadableGames(); }
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    centerloader.showHome();
                }
            }
        }
        
        Rectangle{
            color: design.bgdarkcolor
            height: 64
            width: 64
            Image{
                id: getimage
                anchors.fill: parent
                source: "../resources/get_64.png"
                //style: DesignButton{}
                //onClicked: { centralBox.showDownloadableGames(); }
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    console.log("implement GET button event on /qml/left/main.qml");
                }
            }
        }
        
        Rectangle{
            color: design.bgdarkcolor
            height: 64
            width: 64
            Image{
                id: favimage
                anchors.fill: parent
                source: "../resources/fav_64.png"
                //style: DesignButton{}
                //onClicked: { centralBox.showInstalledGames(); }
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    console.log("implement FAV button event on /qml/left/main.qml");
                }
            }
        }
        
        Rectangle{
            color: design.bgdarkcolor
            height: 64
            width: 64
            Image{
                id: userimage
                anchors.fill: parent
                source: "../resources/user_64.png"
                //style: DesignButton{}
            }
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    centerloader.showSocial();
                }
            }
        }
    }
}
