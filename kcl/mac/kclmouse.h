#ifndef KCLMOUSE_H
#define KCLMOUSE_H

#include "kclinput.h"

#include <QList>
#include <QPoint>
#include <QWidget>

#include <IOKit/hid/IOHIDLib.h>

class KCLMouse : public KCLInput
{
    Q_OBJECT

public:
    KCLMouse(IOHIDDeviceRef device, QObject * parent = 0);

    QPoint position();
    void setSensibility(double s);
    void setOrigin(const QPoint p);
    int wheelPosition() const;
    int hWheelPosition()const;
    double sensibility()const;
    
private:
    QPoint m_position;
    QPoint m_originalPosition;
    double m_sensibility;
};

//@}
#endif // KCLMOUSE_H
