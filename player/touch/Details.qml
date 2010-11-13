import QtQuick 1.0

Rectangle {
    id: gluon_player
    color: "black"

    x: 0
    y: 0

    width: 490
    height: 720

    SystemPalette {
        id: activePalette
    }

       Image {
           id: game_main_img
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

        Button {
            id: play_game_btn
            width: parent.width / 4
            height: parent.height * 1 / 5
            icon: "icons/media-playback-start.png"
            text: "Play The Quantum Sea"
            subtext: "1697 others currently playing"
            onClicked: console.log("this doesn't do anything yet...")
            anchors.left: game_main_img.right
            anchors.margins: 10
        }

        Button {
            id: read_author_desc_btn
            width: parent.width / 4
            height: parent.height * 1 / 5
            icon: "icons/im-user.png"
            text: qsTr("Read Author's Description")
            onClicked: console.log("this doesn't do anything yet...")
            anchors.top: play_game_btn.bottom
            anchors.left: game_main_img.right
            anchors.margins: 10
        }

        Button {
            id: high_scores_btn
            width: parent.width / 2
            height: parent.height * 1 / 5
            icon: "icons/help-hint.png"
            text: qsTr("High Scores")
            subtext: "Your global high-score: 258th"
            onClicked: console.log("this doesn't do anything yet...")
            anchors.top: read_author_desc_btn.bottom
            anchors.left: game_main_img.right
            anchors.margins: 10
        }

        Button {
            id: achievements_btn
            width: parent.width / 2
            height: parent.height * 1 / 5
            icon: "icons/media-playback-start.png"
            text: qsTr("Achievements")
            subtext: "You have 4 of 16"
            onClicked: console.log("this doesn't do anything yet...")
            anchors.top: read_author_desc_btn.bottom
            anchors.left: high_scores_btn.right
            anchors.margins: 10
        }

        Button {
            id: rate_comments_btn
            width: parent.width / 2
            height: parent.height * 1 / 5
            icon: "icons/media-playback-start.png"
            text: qsTr("Rate & Comment")
            subtext: "20984 ratings, 413 comments"
            onClicked: console.log("this doesn't do anything yet...")
            anchors.top: high_scores_btn.bottom
            anchors.left: game_main_img.right
            anchors.margins: 10
        }

        Button {
            id: donate_btn
            width: parent.width / 2
            height: parent.height * 1 / 5
            icon: "icons/media-playback-start.png"
            text: qsTr("Donate")
            subtext: qsTr("€3 suggested")
            onClicked: console.log("this doesn't do anything yet...")
            anchors.top: achievements_btn.bottom
            anchors.left: rate_comments_btn.right
            anchors.margins: 10
        }

        Text {
            id: new_comments
            text: qsTr("New Comments")
            anchors.top: rate_comments_btn.bottom
        }
}
