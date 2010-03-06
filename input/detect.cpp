#include "detect.h"

namespace GluonInput
{
	Detect::Detect(QObject * parent)
	: QObject(parent)
	{
	}

	QList<InputDevice *> Detect::getInputList() {
        return m_inputList;
    }

    QList<KeyBoard *> Detect::getKeyboardList() {
        return m_keyboardList;
    }

    QList<Mouse *> Detect::getMouseList() {
        return m_mouseList;
    }

    QList<Joystick *> Detect::getJoystickList() {
        return m_joystickList;
    }

    QList<Tablet *> Detect::getTabletList() {
        return m_tabletList;
    }

    QList<InputDevice *> Detect::getUnknownDeviceList() {
        return m_unknownList;
    }
}
#include "detect.moc"