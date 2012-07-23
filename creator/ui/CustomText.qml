
import QtQuick 1.0

 Item {
     property variant items: {  'default': qsTr("This is a list of the pre-defined functionality available to you in Gluon Creator. The Components are things like sound emitters and listeners, camera controllers, input handlers and the like, as well as the custom logic handler, the Scripting component.\nClick to continue"),
                                'project': qsTr("This shows all the Assets that you have in your project, such as sounds, textures, scripts, materials and Scenes.\nClick to continue"),
                                'message': qsTr("This is where debugging messages, errors from scripts and other information from the various Components are shown.\nClick to continue"),
                                'scene': qsTr("The contents of the current Scene. This is made up of a tree of GameObjects which in essence is your scene graph.\nClick to continue"),
                                'property': qsTr("The place where you can see and manipulate every option on the various Components which are attached to the GameObjects in your game.\nClick to continue slideshow or press ESC for other options"),
                              }

     function getText(which){
         return items[which];
     }


}
