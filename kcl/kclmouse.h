#ifndef KCLMOUSE_H
#define KCLMOUSE_H
#include "kclinput.h"
#include <QPoint>
#include <QList>
#include <QWidget>
//===============================
// this is a default mouse, with 2 axes, and wheel axes

class KCLMouse : public KCLInput
{
    Q_OBJECT
public:
    KCLMouse(QString device,QObject * parent=0);
    QPoint position(){ return QPoint(axisPosition(REL_X),axisPosition(REL_Y));}
    int wheelPosition(){return axisPosition(REL_WHEEL);}
    int hWheelPosition(){return axisPosition(REL_HWHEEL);}



};

#endif // KCLMOUSE_H
