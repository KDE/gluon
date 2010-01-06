#include "kclmouse.h"

#include <QtCore/QDebug>

KCLMouse::KCLMouse(IOHIDDeviceRef device, QObject *parent)
        : KCLInput(device, parent)
{
    m_originalPosition = QPoint(0, 0);
    m_position = m_originalPosition;
    m_sensibility = 1;
}

QPoint KCLMouse::position()
{
    if ( anyRelMove())
    {
        m_position += QPoint(relAxisValue(m_lastRelAxis), relAxisValue(m_lastRelAxis));
    }
    return (m_position+m_originalPosition)*m_sensibility;
}

void KCLMouse::setSensibility(double s)
{
    m_sensibility=s;
}

void KCLMouse::setOrigin(const QPoint p) 
{
    m_originalPosition = p;
}

int KCLMouse::wheelPosition() const
{
    return relAxisValue(m_lastRelAxis);
}

int KCLMouse::hWheelPosition()const 
{
    return relAxisValue(m_lastRelAxis);
}

double KCLMouse::sensibility()const
{
    return m_sensibility;
}

#include "kclmouse.moc"
