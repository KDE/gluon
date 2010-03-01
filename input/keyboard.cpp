#include "keyboard.h"

using namespace GluonInput;

	/*KeyBoard::KeyBoard(IOHIDDeviceRef device, QObject * parent)
	: InputDevice(device, parent)
	{
	}*/

KeyBoard::KeyBoard(ThreadAbstract * inputThread, QObject * parent) : InputDevice(inputThread, parent)
{
}

#include "keyboard.moc"
