#include "kclmouse.h"
#include <KDebug>
KCLMouse::KCLMouse(QString device, QObject * parent)
        : KCLInput(device, parent)
{
    m_originalPosition = QPoint(0, 0);
    m_position = m_originalPosition;
}

QPoint KCLMouse::position()
{

    m_position = m_originalPosition + QPoint(relAxisValue(REL_X), relAxisValue(REL_Y));
    return m_position;

}
