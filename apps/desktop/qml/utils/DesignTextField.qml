import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

TextFieldStyle {
    textColor: design.txcolor
    background: Rectangle {
        implicitHeight: 25
        implicitWidth: 120
        //border.color: control.pressed ? design.bgdarkcolor : design.txcolor
        color: control.pressed ? design.txcolor : design.bgdarkcolor
        //border.width: 1
    }
}