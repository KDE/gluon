#include "detectabstract.h"

namespace GluonInput
{
	DetectAbstract::DetectAbstract(QObject * parent)
	: QObject(parent)
	{
	}

	QList<InputDevice *> DetectAbstract::getInputList() {
        return m_inputList;
    }

    QList<KeyBoard *> DetectAbstract::getKeyboardList() {
        return m_keyboardList;
    }

    QList<Mouse *> DetectAbstract::getMouseList() {
        return m_mouseList;
    }

    QList<Joystick *> DetectAbstract::getJoystickList() {
        return m_joystickList;
    }

    QList<Tablet *> DetectAbstract::getTabletList() {
        return m_tabletList;
    }

    QList<InputDevice *> DetectAbstract::getUnknownDeviceList() {
        return m_unknownList;
    }
}
#include "detectabstract.moc"