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
    QPoint position();
    void setOrigin(QPoint p){m_originalPosition = p;}
    int wheelPosition(){return relAxisValue(REL_WHEEL);}
    int hWheelPosition(){return relAxisValue(REL_HWHEEL);}

    private:
    QPoint m_position;
    QPoint m_originalPosition;

};

#endif // KCLMOUSE_H
