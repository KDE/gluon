import QtQuick 1.1
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.extras 0.1 as PlasmaExtras
import org.kde.qtextracomponents 0.1 as QtExtraComponents
import Gluon.Player.Desktop 0.72 as GluonPlayer

import ".."
import "../gamelist"

Flickable{
	id: singleGameView
	contentWidth: parent.width
	contentHeight: singlegamebox.height
	flickableDirection: Flickable.VerticalFlick
	clip: false
	boundsBehavior: Flickable.StopAtBounds
	
	anchors.left: parent.left;
	anchors.right: parent.right;

	width: parent.width;
	
	BackgroundBox{ target: singlegamebox; }
	
	property string gameId;
	
	GluonPlayer.GameMetadata
	{
		id: gameMetadata
		gameId: singleGameView.gameId
	}
	
	Column{
		id: singlegamebox;
		anchors.top: parent.top
		anchors.bottomMargin: 20
		
		width: parent.width;
		spacing: 10;
		Item{
			id:singlegamebox_imagebox;
			width: parent.width
			height: 360;
			
			PlasmaComponents.BusyIndicator{
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
		
		
		PlasmaExtras.Title{
			id: singlegamebox_title
			text: gameMetadata.gameName;
			Text{
				anchors.left: parent.right
				anchors.bottom: parent.bottom
				text:" (version "+gameMetadata.gameVersion+")";
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
		}
		
		Rectangle{
			anchors.left: parent.left
			anchors.right: parent.right
			height:1;
 			color: "#000000"
		}
		
		PlasmaExtras.Heading{
			level: 2;
			text: "Features:";
		}
		Text{
			anchors.left: parent.left
			anchors.right: parent.right
			anchors.leftMargin: 20
			wrapMode: Text.WordWrap
			font.pixelSize: 13
			text: gameMetadata.gameDescription
		}
		
		Rectangle{
			anchors.left: parent.left
			anchors.right: parent.right
			height:1;
 			color: "#000000"
		}
		
		PlasmaExtras.Heading{
			level: 2;
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
		}
		
		Rectangle{
			anchors.left: parent.left
			anchors.right: parent.right
			height:1;
 			color: "#000000"
		}
		
		PlasmaExtras.Heading{
			id: singlegamebox_commentsh
			level: 2;
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