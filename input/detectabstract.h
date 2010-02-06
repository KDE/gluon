#ifndef DETECTABSTRACT_H
#define DETECTABSTRACT_H

#include <QtCore/QObject>

#include "gluoninput.h"

namespace GluonInput
{
	class Joystick;
	class Mouse;
	class Tablet;
	class KeyBoard;
	class InputDevice;

	class GLUONINPUTSHARED_EXPORT DetectAbstract : public QObject 
	{
		Q_OBJECT

	public:
		DetectAbstract(QObject * parent = 0);
		
		virtual void searchDevice() = 0;
		virtual void setAllEnabled() = 0;
		virtual void setAllDisabled() = 0;
		
		virtual QList<InputDevice *> getInputList() = 0;    
		virtual QList<KeyBoard *> getKeyboardList() = 0;
		virtual QList<Mouse *> getMouseList() = 0;
		virtual QList<Joystick *> getJoystickList() = 0;
		virtual QList<Tablet *> getTabletList() = 0;
		virtual QList<InputDevice *> getUnknownDeviceList() = 0;    
		
		virtual void addInput(InputDevice *i) = 0;
		virtual void addKeyboard(InputDevice *i) = 0;
		virtual void addMouse(InputDevice *i) = 0;
		virtual void addJoystick(InputDevice *i) = 0;
		virtual void addTablet(InputDevice *i) = 0;
		virtual void addUnknown(InputDevice *i) = 0;
		virtual void clear() = 0;
		
	protected:
		QList<InputDevice *> m_inputList;
		QList<KeyBoard *> m_keyboardList;
		QList<Mouse *> m_mouseList;
		QList<Joystick *> m_joystickList;
		QList<Tablet *> m_tabletList;
		QList<InputDevice *> m_unknownList;
		
	};
}
#endif 