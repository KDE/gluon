import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

ButtonStyle {
    background: Rectangle {
        implicitHeight: 25
        implicitWidth: 120
        //border.width: 1
        //border.color: control.pressed ? design.bgdarkcolor : design.txcolor
        color: control.pressed ? design.txcolor : design.bgdarkcolor
    }
    label: Label {
        horizontalAlignment: Text.AlignHCenter
        color: control.pressed ? design.bgdarkcolor : design.txcolor
        text: control.text
    }
} 
