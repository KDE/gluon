#include "kclkeyboard.h"
#include <KDebug>
KCLKeyBoard::KCLKeyBoard(const QString& device, QObject * parent)
    :KCLInput(device, parent)
{
}

void KCLKeyBoard::inputEventFilter(KCLInputEvent * event)
{


    switch ( event->type())
    {

    case  EV_KEY:
        setRelPosition(QPoint(0,0));
        if ((event->code()== KEY_UP) && ( event->value() == 1))
            setRelPosition(QPoint(0,-1));


        if ((event->code()== KEY_DOWN) && ( event->value() == 1))
            setRelPosition(QPoint(0,1));


        if ((event->code()== KEY_LEFT) && ( event->value() == 1))
            setRelPosition(QPoint(-1,0));


        if ((event->code()== KEY_RIGHT) && ( event->value() == 1))
            setRelPosition(QPoint(1,0));



        break;




    }



}
