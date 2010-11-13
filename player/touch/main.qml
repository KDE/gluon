import QtQuick 1.0

Item {
    id: gluon_player

    x: 0
    y: 0

    width: 1028
    height: 768

    Startup {
        visible: true
    }

    Registration {
        visible: false
    }

    Home {
        visible: false
    }

    Details {
        visible: false
    }

    Comments {
        visible: false
    }
}

