#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "inputdevice.h"

namespace GluonInput
{
	class ThreadAbstract;

	class GLUON_INPUT_EXPORT KeyBoard : public InputDevice
	{
	public:
		//KeyBoard(IOHIDDeviceRef device, QObject * parent = 0);
		KeyBoard(ThreadAbstract * inputThread, QObject * parent = 0);
	};
}
#endif // KCLKEYBOARD_H
