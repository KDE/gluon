import QtQuick 1.0

Rectangle {
    id: gluon_player
    color: "black"

    width: 490
    height: 720

    SystemPalette {
        id: activePalette
    }

       Image {
           id: gluon_logo
           // anchors.fill: parent
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
            width: parent.width / 2
            height: parent.height * 2 / 5
            anchors.left: gluon_logo.right
            anchors.margins: 10
        }

        Button {
            id: new_user
            width: parent.width / 4
            height: parent.height * 1 / 5
            icon: "icons/user-group-new.png"
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
            width: parent.width / 4
            height: parent.height * 1 / 5
            icon: "icons/im-user.png"
            text: "Log On"
            onClicked: {
                authentication.login(lgn.username, lgn.password)
                state: LogOnState
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
                state: forgottenDetailsState
            }
            subtext: "Send new password to your email address"
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
                state: playState
            }
            subtext: "3 games available"
            anchors.top: forgotten_details.bottom
            anchors.left: gluon_logo.right
            anchors.margins: 10
        }
}
