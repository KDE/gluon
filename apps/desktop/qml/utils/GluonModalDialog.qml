import QtQuick 2.2
import QtQuick.Controls 1.1

import "../utils"
    
Rectangle{
    id:modalDialogBox
    
    color: design.fgcolor
    
    property Item target;
    property int space: 10;
    
    anchors.left: target.left;
    anchors.right:target.right;
    anchors.top: target.top;
    anchors.bottom: target.bottom;
    
    anchors.leftMargin: -space;
    anchors.rightMargin: -space;
    anchors.topMargin: -space;
    anchors.bottomMargin:-space;
    
    radius: 5;
}
