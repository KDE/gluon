import QtQuick 1.1
import org.kde.plasma.core 0.1 as PlasmaCore
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.extras 0.1 as PlasmaExtras

Item {
    id: base;

    property alias headerText: headerTextItem.text;
    property bool headerVisible: true;

    property alias model: itemView.model;
    property string dataRole: "modelData";
    property alias listHeader: itemView.header;

    signal itemClicked( int index );

    Item {
        id: header;

        anchors {
            top: parent.top;
            left: parent.left;
            right: parent.right;
        }

        height: base.headerVisible ? 35 : 0;
        Behavior on height { NumberAnimation { } }

        clip: true;

        PlasmaExtras.Heading {
            id: headerTextItem;

            width: parent.width;
            text: "News";
            level: 2;
            horizontalAlignment: Text.AlignHCenter;
        }
    }

    PlasmaCore.FrameSvgItem {
        anchors {
            top: header.bottom;
            left: parent.left;
            right: parent.right;
            bottom: parent.bottom;
        }

        imagePath: "widgets/frame";
        prefix: "sunken";

        MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onEntered: itemView.highlightItem.opacity = 1;
            onPositionChanged: { var index = itemView.indexAt(mouse.x, mouse.y + itemView.contentY); if( index != -1 ) itemView.currentIndex = index }
            onExited: itemView.highlightItem.opacity = 0;
        }

        PlasmaExtras.ScrollArea {
            anchors.fill: parent;
            ListView {
                id: itemView;
                clip: true;

                delegate: listDelegate;
                highlight: listHighlight;
            }
        }
    }

    Component {
        id: listDelegate;

        Item {
            width: parent.width;
            height: 50;
            PlasmaComponents.Label {
                anchors {
                    left: parent.left;
                    leftMargin: 10;
                    right: parent.right;
                    rightMargin: 10;
                    verticalCenter: parent.verticalCenter;
                }
                elide: Text.ElideLeft;
                text: model[base.dataRole];
            }

            MouseArea {
                anchors.fill: parent;

                onClicked: base.itemClicked( index );
            }
        }
    }

    Component {
        id: listHighlight;

        PlasmaComponents.Highlight {
            opacity: 0;
            Behavior on opacity { NumberAnimation { } }
        }
    }
}
