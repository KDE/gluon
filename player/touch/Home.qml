import QtQuick 1.0

Rectangle {
    anchors.fill: parent
    Button {
        id: new_user
        width: parent.width / 4
        height: parent.height * 1 / 5
        icon: "icons/get-hot-new-stuff.png"
        text: qsTr("Get More Games")
        subtext: "5 new games, 16 updated"
        onClicked: console.log("this doesn't do anything yet...")
    }
}
