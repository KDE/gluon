#include "mouse.h"
#include "mouseprivate.h"

#include <QtCore/QDebug>

namespace GluonInput
{
    Mouse::Mouse(InputThread * inputThread, QObject * parent) : InputDevice(inputThread, parent)
    {
        d = new MousePrivate();
        d->m_originalPosition = d->m_position = QPoint(0, 0);
        d->m_sensibility = 1;
    }

    QPoint Mouse::position()
    {
        if (anyRelMove())
        {
            d->m_position += QPoint(relAxisValue(lastRelAxis()), relAxisValue(lastRelAxis()));
        }
        return (d->m_position + d->m_originalPosition)*d->m_sensibility;
    }

    void Mouse::setSensibility(double s)
    {
        d->m_sensibility = s;
    }

    void Mouse::setOrigin(const QPoint p)
    {
        d->m_originalPosition = p;
    }

    int Mouse::wheelPosition() const
    {
        return relAxisValue(lastRelAxis());
    }

    int Mouse::hWheelPosition()const
    {
        return relAxisValue(lastRelAxis());
    }

    double Mouse::sensibility()const
    {
        return d->m_sensibility;
    }
}
#include "mouse.moc"
