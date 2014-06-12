import QtQuick 2.2
import "../utils"
import "highlights"
import "gamelist"

Column{
    
    Box{
        id: userbox_bg
        width: parent.width
        //source on /qml/center/highlights
        HighlightBox{}
        
        Component.onCompleted:{
            height = childrenRect.height +40
        }
    }
    
    Box{
        id: downloadablelist_bg
        width: parent.width
        
        Component.onCompleted:{
            height = childrenRect.height +40
        }
        
        onChildrenRectChanged:{
            height = childrenRect.height +40
        }
        
        DownloadableList{}
    }
}
