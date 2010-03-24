#ifndef GLUONDEVICES_H
#define GLUONDEVICES_H

#include <QtCore/QFlags>
#include <QtCore/QEvent>

#include <IOKit/hid/IOHIDUsageTables.h>

namespace GluonInput 
{
	enum DeviceFlag 
	{
		UnknownDevice = kHIDUsage_Undefined,
		KeyboardDevice = kHIDUsage_GD_Keyboard,
		MouseDevice = kHIDUsage_GD_Mouse,
		JoystickDevice = kHIDUsage_GD_Joystick,
		//TouchpadDevice = kHIDUsage_Dig_TouchPad, //this belongs under the category of digitizers
		TabletDevice = kHIDUsage_Dig_Digitizer //change this because there exist alot of different kinds of tablets
	};
	Q_DECLARE_FLAGS(Devices, DeviceFlag)
	
	Q_DECLARE_OPERATORS_FOR_FLAGS(Devices);
}

#endif