import QtQuick 2.2

Text{
    property int level;
    
    color: design.txcolor
    
    font.pointSize: (7-level)*4
}
