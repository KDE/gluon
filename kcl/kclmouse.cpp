#include "kclmouse.h"

#include <QDebug>

KCLMouse::KCLMouse(const QString &device, QObject *parent)
        : KCLInput(device, parent)
{
    m_originalPosition = QPoint(0, 0);
    m_position = m_originalPosition;
    m_sensibility = 1;
}

QPoint KCLMouse::position()
{
    if ( anyRelMove())
    m_position += QPoint(relAxisValue(REL_X), relAxisValue(REL_Y));
    return (m_position+m_originalPosition)*m_sensibility;
}
