#ifndef DETECT_H
#define DETECT_H

#include <QtCore/QObject>
#include <QtCore/QList>

#include "detectabstract.h"
#include "inputdevice.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "tablet.h"
#include "core/singleton.h"

namespace GluonInput
{
	typedef QList<InputDevice *> InputList;

	class GLUON_INPUT_EXPORT Detect : public GluonCore::Singleton<Detect>
	{
		Q_OBJECT

	public:
		Detect();
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
		~Detect();
		DetectAbstract * m_instance;
		void init();
	};
}

#endif
