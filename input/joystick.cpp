#include "joystick.h"

namespace GluonInput
{
	/*Joystick::Joystick(IOHIDDeviceRef device, QObject * parent)
			: InputDevice(device, parent)
	{
	}*/
	
	Joystick::Joystick(InputThread * inputThread, QObject * parent)	: InputDevice(inputThread, parent)
	{
	}

	int Joystick::axisX() const
	{
		return absAxisValue(inputListener->getJoystickXAxis());
	}

	int Joystick::axisY()const 
	{
		return absAxisValue(inputListener->getJoystickYAxis());
	}

	int Joystick::axisZ() const
	{
		return absAxisValue(inputListener->getJoystickZAxis());
	}
}
#include "joystick.moc"
