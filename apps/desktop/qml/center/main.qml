import QtQuick 2.2
import "../utils"
import "highlights"
import "gamelist"

Column{
    
    Box{
        id: userbox_bg
        width: parent.width
        height: childrenRect.height
        //source on /qml/center/highlights
        HighlightBox{}
        
    }
    
    Box{
        id: downloadablelist_bg
        width: parent.width
        
        Component.onCompleted:{
            height = childrenRect.height +32
        }
        
        onChildrenRectChanged:{
            height = childrenRect.height +32
        }
        
        DownloadableList{}
    }
}
