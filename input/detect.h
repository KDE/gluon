#ifndef DETECT_H
#define DETECT_H

#include "gluoninput.h"

#include "detectabstract.h"

#include <QtCore/QObject>
#include <QtCore/QList>

#include "inputdevice.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "tablet.h"

namespace GluonInput
{
	typedef QList<InputDevice *> InputList;

	class GLUONINPUTSHARED_EXPORT Detect : public QObject
	{
		Q_OBJECT

	private:
		Detect(QObject * parent);
		~Detect();

	public:
		static void searchDevice();
		static void setAllEnable();
		static void setAllDisable();

		static unsigned int deviceCount();

		static unsigned int keyboardCount();

		static unsigned int mouseCount();

		static unsigned int joystickCount();

		static unsigned int tabletCount();

		static unsigned int unknownDeviceCount();

		static QList <KeyBoard*> keyboardList();

		static QList <Mouse*> mouseList();

		static QList <Joystick*> joystickList();

		static QList <Tablet*> tabletList();

		static QList <InputDevice*> unknownDeviceList();

		static InputList inputList();

		static KeyBoard* keyboard(int id = 0);

		static Mouse* mouse(int id = 0);

		static Joystick* joystick(int id = 0);

		static Tablet* tablet(int id = 0);

		static InputDevice* input(int id = 0);

	private:
		static DetectAbstract * m_instance;
		static void init();
	};
}

#endif
