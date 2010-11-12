import Qt 4.7

Rectangle {
    Button {
        id: new_user
        width: parent.width / 4
        height: parent.height * 1 / 5
        icon: "icons/user-group-new.png"
        text: "Get More Games"
        subtext: "5 new games, 16 updated"
        onClicked: console.log("this doesn't do anything yet...")
    }
}
