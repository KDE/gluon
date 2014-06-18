import QtQuick 2.2


Rectangle{
    
    property alias text: areatextedit.text;
    property alias readOnly: areatextedit.readOnly;
    
    color: design.bgdarkcolor
    
    TextEdit{
        id: areatextedit
        
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        anchors.bottomMargin: 5
        anchors.topMargin: 5
        
        color: design.txcolor
    }
}
