import Qt 4.7

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


        Button {
            id: comment
            icon: "icons/user-group-new.png"
            text: "gamerdude"
            onClicked: console.log("this doesn't do anything yet...")
        }
}
