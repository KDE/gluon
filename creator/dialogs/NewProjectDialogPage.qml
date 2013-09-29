import QtQuick 1.1
import org.kde.plasma.components 0.1 as PlasmaComponents
import org.kde.plasma.extras 0.1 as PlasmaExtras

PlasmaComponents.Page {
    id: base;

    Item {
        anchors.fill: parent;

        Column {
            anchors.fill: parent;
            anchors.margins: 10;
            spacing: 5;

            PlasmaExtras.Heading {
                width: parent.width;
                text: "Create Empty Project";
                horizontalAlignment: Text.AlignHCenter;
                level: 2;
            }
            PlasmaComponents.Label {
                text: "Project Name";
            }
            PlasmaComponents.TextField {
                id: projectNameField;
                width: parent.width;
            }
            PlasmaComponents.Label {
                text: "Location";
            }
            Row {
                width: parent.width;

                PlasmaComponents.TextField {
                    id: locationField;
                    width: parent.width - selectDirIcon.width;
                }

                PlasmaComponents.Button {
                    id: selectDirIcon;
                    iconSource: "folder-open";
                    onClicked: locationField.text = mainWindow.selectDirectory();
                }
            }
            PlasmaComponents.Label {
                id: projectNameErrorText;

                text: "Project name cannot be empty.";
                color: "red";

                opacity: projectNameField.text == "";
                Behavior on opacity { NumberAnimation { } }
            }

            PlasmaComponents.Label {
                id: locationErrorText;

                text: "Location cannot be empty.";
                color: "red";

                opacity: locationField.text == "";
                Behavior on opacity { NumberAnimation { } }
            }
        }

        PlasmaComponents.Button {
            anchors {
                bottom: parent.bottom;
                bottomMargin: 5;
                right: parent.horizontalCenter;
                rightMargin: 10;
            }
            text: "Ok";

            onClicked: {
                if( projectNameField.text === "" || locationField.text === "" )
                    return;

                mainWindow.createProject( projectNameField.text, locationField.text );
            }
        }

        PlasmaComponents.Button {
            anchors {
                bottom: parent.bottom;
                bottomMargin: 5;
                left: parent.horizontalCenter;
                leftMargin: 10;
            }
            text: "Cancel";

            onClicked: pageStack.pop();
        }
    }
}
