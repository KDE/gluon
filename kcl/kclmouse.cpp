#include "kclmouse.h"
#include <KDebug>
KCLMouse::KCLMouse(QString device,QObject * parent)
    :KCLInput(device,parent),m_position(QPoint(0,0))
{

}

