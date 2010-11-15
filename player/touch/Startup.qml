import QtQuick 1.0

Rectangle {

    color: "black"
    anchors.fill: parent

   Image {
       id: gluon_logo
       source: "icons/hi256-app-gluon.png"
       width: parent.width/2 * 4/5
       height: parent.height * 3/5
       fillMode: Image.PreserveAspectFit
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.horizontalCenterOffset: -parent.width/4
       anchors.verticalCenter: parent.verticalCenter
       anchors.margins: 10
   }

    Login {
        id: lgn
        objectName: "login"
        width: parent.width / 2
        height: parent.height * 2 / 5
        anchors.left: gluon_logo.right
        anchors.margins: 10
    }

    Button {
        id: new_user
        width: parent.width / 4 - 5
        height: parent.height * 1 / 5
        icon: "icons/list-add-user.png"
        text: "New User"
        onClicked: {
            mainview.statepoint = "registration"
        }
        anchors.top: lgn.bottom
        anchors.left: gluon_logo.right
        anchors.margins: 10
    }

    Button {
        id: log_on
        width: parent.width / 4 - 5
        height: parent.height * 1 / 5
        icon: "icons/im-user.png"
        text: "Log On"
        onClicked: {
            if (lgn.providerInitialized) {
                console.log("Provider have been already initialized!")
                authentication.login(lgn.username, lgn.password)
                mainview.statepoint = "home"
            } else {
                console.log("Provider is not initialized yet!")
            }
        }
        anchors.top: lgn.bottom
        anchors.left: new_user.right
        anchors.margins: 10
    }

    Button {
        id: forgotten_details
        width: parent.width / 2
        height: parent.height * 1 / 5
        icon: "icons/help-hint.png"
        text: "Forgotten Your Details?"
        onClicked: {
            mainview.statepoint = "forgottenDetails"
        }
        subtext: qsTr("Send new password to your email address")
        anchors.top: log_on.bottom
        anchors.left: gluon_logo.right
        anchors.margins: 10
    }

    Button {
        id: play
        width: parent.width / 2
        height: parent.height * 1 / 5
        icon: "icons/media-playback-start.png"
        text: "Play Without Logging On"
        onClicked: {
            mainview.statepoint = "home"
        }
        subtext: "3 games available"
        anchors.top: forgotten_details.bottom
        anchors.left: gluon_logo.right
        anchors.margins: 10
    }
}
