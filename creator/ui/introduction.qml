import QtQuick 1.0

Item {

    Rectangle {
        id: topOverlay;

        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: viewport.top;

        opacity: 0.1;
        color: "blue";
    }
    Rectangle {
        id: leftOverlay;

        anchors.top: topOverlay.bottom;
        anchors.left: parent.left;
        anchors.right: viewport.left;
        anchors.bottom: bottomOverlay.top;

        opacity: 0.1;
        color: "blue";
    }
    Rectangle {
        id: rightOverlay;

        anchors.top: topOverlay.bottom;
        anchors.left: viewport.right;
        anchors.right: parent.right;
        anchors.bottom: bottomOverlay.top;

        opacity: 0.1;
        color: "blue";
    }
    Rectangle {
        id: bottomOverlay;

        anchors.top: viewport.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;

        opacity: 0.1;
        color: "blue";
    }

    Item {
        id: geomtery
        width: 0;
        height: 0;
        x: 0;
        y: 0;
        }

    Item {
        id: viewport;

        width: parent.width / 2;
        height: parent.height / 2;
        x: parent.width / 4;
        y: parent.height / 4;

        Behavior on width { NumberAnimation { duration: 500; } }
        Behavior on height { NumberAnimation { duration: 500; } }
        Behavior on x { NumberAnimation { duration: 500; } }
        Behavior on y { NumberAnimation { duration: 500; } }

    states: [

        State {
                name: "next"
                PropertyChanges { target: viewport; x: componentsDockRect.x; y: componentsDockRect.y; width:componentsDockRect.width; height:componentsDockRect.height }
            },

        State {
                name: "next2"
                PropertyChanges { target: viewport; x: projectDockRect.x; y: projectDockRect.y; width: projectDockRect.width; height: projectDockRect.height }
            }
    ]

        // Transitions define how the properties change when the item moves between each state
    transitions: [

            Transition {
                from: "*"; to: "next"
                NumberAnimation { properties: "x,y,width,height"; duration: 1000 }
            },

            Transition {
                from: "*"; to: "next2"
                NumberAnimation { properties: "x,y,width,height"; duration: 1000 }
            }
        ]

    }

    MouseArea {anchors.fill: parent; onClicked: viewport.state = 'next' }
    Rectangle {
            id: componentsDockRect
            opacity: 0.1;
            color: "blue";
            x : targetRect.x;
            y : targetRect.y;
            width : targetRect.width;
            height : targetRect.height;
            MouseArea { anchors.fill: parent; onEntered: viewport.state = 'next2' }

        }

}
