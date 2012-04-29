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
        id :dummy;
        property string dockername:"";
        x:0;
        y :0;
        width :0;
        height :0;
        onDockernameChanged : intro.updateDocker(dockername);
        objectName: "geometry";
    }

    Item {
        id: viewport;
        property int flag: 0
        width: parent.width / 2;
        height: parent.height / 2;
        x: parent.width / 4;
        y: parent.height / 4;

        Behavior on width { NumberAnimation { duration: 500; } }
        Behavior on height { NumberAnimation { duration: 500; } }
        Behavior on x { NumberAnimation { duration: 500; } }
        Behavior on y { NumberAnimation { duration: 500; } }

    MouseArea {
        anchors.fill: parent;

        onClicked: {
            switch(flag){
            case(0):
                viewport.state = 'component';
                break;
            case(1):
                viewport.state = 'project';
                break;
            default:
                break;

            }
        }

    }
    states: [

        State {
                name: "component"
                PropertyChanges { target:dummy; dockername : "ComponentsDock"}
                PropertyChanges { target: viewport; flag:1; x: dummy.x; y: dummy.y; width:dummy.width; height:dummy.height }
            },

        State {
                name: "project"
                PropertyChanges { target:dummy; dockername : "ProjectsDock"}
                PropertyChanges { target: viewport;flag:2 ; x: dummy.x; y: dummy.y; width:dummy.width; height:dummy.height }
            }
    ]

    transitions: [

            Transition {
                from: "*"; to: "component"
                NumberAnimation { properties: "x,y,width,height"; duration: 1000 }
            },

            Transition {
                from: "*"; to: "project"
                NumberAnimation { properties: "x,y,width,height"; duration: 1000 }
            }
        ]

    }


}
