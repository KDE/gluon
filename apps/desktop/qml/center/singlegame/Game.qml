import QtQuick 2.2
import Gluon.Player.Desktop 0.72 as GluonPlayer
import QtQuick.Controls 1.1

import "../../utils"
import "../gamelist"

Flickable{
    id: singleGameView
    contentWidth: parent.width
    contentHeight: singlegamebox.height + 40  //20 pixels margin top + 20 margin bottom
    flickableDirection: Flickable.VerticalFlick
    clip: false
    boundsBehavior: Flickable.StopAtBounds
    
    anchors.left: parent.left;
    anchors.right: parent.right;

    width: parent.width;
    
    property string gameId;
    
    GluonPlayer.GameMetadata
    {
        id: gameMetadata
        gameId: singleGameView.gameId
    }
    
    
    Box {
        anchors.fill: parent
        
        Column{
            id: singlegamebox;
            anchors.top: parent.top
            anchors.topMargin: 20
            
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            
            spacing: 10;
            Item{
                id:singlegamebox_imagebox;
                width: parent.width
                height: 360;
                
                BusyIndicator{
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    running: true
                }
                
                Image{
                    id: singlegamebox_image;
                    source: gameMetadata.gamePreviewPicture;
                    width: parent.width
                    height: parent.height;
                }
            }
            
            
            Text{
                id: singlegamebox_title
                text: gameMetadata.gameName;
                Text{
                    anchors.left: parent.right
                    anchors.bottom: parent.bottom
                    text:" (version "+gameMetadata.gameVersion+")";
                    color: design.txcolor
                }
            }
            
            Rating {
                    anchors.top: singlegamebox_title.top
                    anchors.right: parent.right
                    rate: gameMetadata.gameRating;
            }
            
            Text{
                anchors.left: parent.left
                anchors.right: parent.right
                wrapMode: Text.WordWrap
                font.bold: true
                font.pixelSize: 16
                text: gameMetadata.gameSummary
                color: design.txcolor
            }
            
            Line{}
            
            Heading{
                level: 3;
                text: "Features:";
            }
            Text{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 20
                wrapMode: Text.WordWrap
                font.pixelSize: 13
                text: gameMetadata.gameDescription
                color: design.txcolor
            }
            
            Line{}
            
            Heading{
                level: 3;
                text: "Changelog:";
            }
            
            Text{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 20
                wrapMode: Text.WordWrap
                font.pixelSize: 13
                font.family: "monospace"
                text: gameMetadata.gameChangelog
                color: design.txcolor
            }
            
            Line{}
            
            Heading{
                id: singlegamebox_commentsh
                level: 3;
                text: "Comments:";
            }
            
            CommentsView {
                id: gameCommentsView
                gameId: gameMetadata.gameId
                width: parent.width
            }
            
            AddCommentForm{
                parentId: singleGameView.gameId
                
                onAddComment:{
                    gameCommentsView.model.uploadComment(parentId, subjectText, bodyText);
                }
            }
        }
    }
} 
