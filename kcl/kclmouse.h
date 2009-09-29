#ifndef KCLMOUSE_H
#define KCLMOUSE_H

#include "kclinput.h"

#include <QList>
#include <QPoint>
#include <QWidget>

/**
 * \defgroup KCL KCL
 */
//@{

// this is a default mouse, with 2 axes, and wheel axes

class KCL_EXPORT KCLMouse : public KCLInput
{
    Q_OBJECT

public:
    KCLMouse(QString device, QObject * parent = 0);

    QPoint position();
    void setSensibility(double s){
    m_sensibility=s;
    }
    void setOrigin(QPoint p) {
        m_originalPosition = p;
    }

    int wheelPosition() const{
        return relAxisValue(REL_WHEEL);
    }

    int hWheelPosition()const {
        return relAxisValue(REL_HWHEEL);
    }
    double sensibility()const{
        return m_sensibility;
            }

private:
    QPoint m_position;
    QPoint m_originalPosition;
    double m_sensibility;
};

//@}
#endif // KCLMOUSE_H
