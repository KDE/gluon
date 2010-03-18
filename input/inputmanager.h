#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QSharedData>

#include "inputdevice.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "tablet.h"
#include "core/singleton.h"

namespace GluonInput
{
	typedef QList<InputDevice *> InputList;

    class InputManagerPrivate;

	class GLUON_INPUT_EXPORT InputManager : public GluonCore::Singleton<InputManager>
	{
		Q_OBJECT

	public:
		InputManager();
		void searchDevice();
		void setAllEnable();
		void setAllDisable();

		unsigned int deviceCount();

		unsigned int keyboardCount();

		unsigned int mouseCount();

		unsigned int joystickCount();

		unsigned int tabletCount();

		unsigned int unknownDeviceCount();

		QList <KeyBoard*> keyboardList();

		QList <Mouse*> mouseList();

		QList <Joystick*> joystickList();

		QList <Tablet*> tabletList();

		QList <InputDevice*> unknownDeviceList();

		InputList inputList();

		KeyBoard* keyboard(int id = 0);

		Mouse* mouse(int id = 0);

		Joystick* joystick(int id = 0);

		Tablet* tablet(int id = 0);

		InputDevice* input(int id = 0);

	private:
		~InputManager();
		void init();

		QSharedDataPointer<InputManagerPrivate> d;
	};
}

#endif
