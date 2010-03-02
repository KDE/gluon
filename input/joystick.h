#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "inputdevice.h"

namespace GluonInput
{
	class InputThread;

	class GLUON_INPUT_EXPORT Joystick : public InputDevice
	{
		Q_OBJECT
	public:
		//Joystick(IOHIDDeviceRef device, QObject * parent = 0);
		Joystick(InputThread * inputThread, QObject * parent = 0);

		int axisX() const;
		int axisY()const;
		int axisZ() const;
	};
}
//@}
#endif // KCLJOYSTICK_H
