import QtQuick 2.2
import Gluon.Player.Desktop 0.72 as GluonPlayer
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0

import "../../utils"
import "../gamelist"

Flickable{
    id: socialView
    contentWidth: parent.width
    contentHeight: socialBox.height + 40  //20 pixels margin top + 20 margin bottom
    flickableDirection: Flickable.VerticalFlick
    clip: false
    boundsBehavior: Flickable.StopAtBounds
    
    anchors.left: parent.left;
    anchors.right: parent.right;

    width: parent.width;
    
    property string gameId;    
    
    Box {
        anchors.fill: parent
        Column{
            id:socialBox
            anchors.left:parent.left
            anchors.right:parent.right
            anchors.leftMargin:20
            anchors.rightMargin:20
            anchors.top: parent.top
            anchors.topMargin: 20
            spacing: 10
            Item{
                width:parent.width
                height: childrenRect.height
                
                Heading{
                    id: searchFriendHeading
                    level: 2
                    text: "Search a friend"
                }
                
                TextField{
                    id:searchFriendTextField
                    anchors.top:searchFriendButton.top
                    anchors.left: parent.left
                    anchors.right: searchFriendButton.left
                    anchors.rightMargin: 10
                    style: DesignTextField{}
                }
                
                Button{
                    id:searchFriendButton
                    anchors.top:searchFriendHeading.bottom
                    anchors.topMargin: 10
                    anchors.right:parent.right
                    text: "search"
                    style: DesignButton{}
                    
                    onClicked:{
                        personsModel.searchByName(searchFriendTextField.text);
                    }
                }
                
            }
            
            Line{}
            
            Text{
                id: personsnothingfound
                color: design.txcolor
                text: "No user found."
            }
            
            Repeater {
                id: personsListView
                
                model: GluonPlayer.PersonsModel { id: personsModel }
                delegate: PersonDelegate{}
                
                onItemAdded:{
                    if(personsListView.count==0){
                        personsnothingfound.visible = true;
                    } else {
                        personsnothingfound.visible = false;
                    }
                }
                onItemRemoved:{
                    if(personsListView.count==0){
                        personsnothingfound.visible = true;
                    } else {
                        personsnothingfound.visible = false;
                    }
                }
            }
            
            Line{ }
            
            Item{
                width:parent.width
                height: childrenRect.height
                
                Heading{
                    id: activitiesHeading
                    level: 2
                    text: "Friend activities"
                }
                
                TextField{
                    id:postActivityTextField
                    anchors.top:postActivityButton.top
                    anchors.left: parent.left
                    anchors.right: postActivityButton.left
                    anchors.rightMargin: 10
                    style: DesignTextField{}
                }
                
                Button{
                    id:postActivityButton
                    anchors.top:activitiesHeading.bottom
                    anchors.topMargin: 10
                    anchors.right:parent.right
                    text: "post message"
                    style: DesignButton{}
                    
                    //TODO: manage success and fail of message posting
                    onClicked:{
                        activitymodelsocial.postActivity(postActivityTextField.text);
                        notification.open("Message successfully posted!");
                    }
                }
                
            }
            
            Text{
                id: activitiesnothingfound
                color: design.txcolor
                text: "No activities found."
            }
            
            Repeater {
                id: activityListView
                
                function setLogged(){
                    activitymodelsocial.fetchActivities();
                }
                
                model: GluonPlayer.ActivityModel{ id: activitymodelsocial}
                delegate: ActivityDelegate{}
                
                function ifEmpty(){
                    if(activityListView.count==0){
                        activitiesnothingfound.visible = true;
                    } else {
                        activitiesnothingfound.visible = false;
                    }
                }
                
                onItemAdded:{
                    ifEmpty();
                }
                onItemRemoved:{
                    ifEmpty();
                }
                
                Component.onCompleted:{
                    loginscreen.onLoginCompleted.connect(setLogged);
                    ifEmpty();
                }
            }
        }
        
    }
} 
