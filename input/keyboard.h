#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "gluoninput.h"
#include "inputdevice.h"

namespace GluonInput
{
	class ThreadAbstract;
	
	class GLUONINPUTSHARED_EXPORT KeyBoard : public InputDevice
	{
	public:
		//KeyBoard(IOHIDDeviceRef device, QObject * parent = 0);
		KeyBoard(ThreadAbstract * inputThread, QObject * parent = 0);
	};
}
#endif // KCLKEYBOARD_H
