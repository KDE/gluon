import QtQuick 1.0

Item {
    id: mainview
    property string statepoint: "start"

    width: 1600
    height: 900

    SystemPalette {
        id: activePalette
    }

    states: [
        State { name: "startup"; when: statepoint == "startup"
            PropertyChanges { }
        },

        State { name: "registration"; when: statepoint == "registration"
            PropertyChanges { }
        },

        State { name: "home"; when: statepoint == "home"
            PropertyChanges { }
        },

        State { name: "details"; when: statepoint == "details"
            PropertyChanges { }
        },

        State { name: "comments"; when: statepoint == "comments"
            PropertyChanges { }
        },

        State { name: "other"; when: statepoint == "other" }
    ]

    Startup {
        height: parent.height
        width: parent.width
        visible: statepoint == "startup"
    }

    Registration {
        height: parent.height
        width: parent.width
        visible: statepoint == "registration"
    }

    Home {
        height: parent.height
        width: parent.width
        visible: statepoint == "home"
    }

    Details {
        height: parent.height
        width: parent.width
        visible: statepoint == "details"
    }

    Comments {
        height: parent.height
        width: parent.width
        visible: statepoint == "comments"
    }

    Component.onCompleted: {
        statepoint = "startup"
    }
}

