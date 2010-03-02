#include "tablet.h"

namespace GluonInput
{
	/*Tablet::Tablet(IOHIDDeviceRef device, QObject *parent)
			: InputDevice(device, parent)
	{
	}*/
	
	Tablet::Tablet(InputThread * inputThread, QObject * parent) : InputDevice(inputThread, parent)
	{
	}
}
