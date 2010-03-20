#include "keyboard.h"
#include "keyboardprivate.h"

using namespace GluonInput;

Keyboard::Keyboard(InputThread * inputThread, QObject * parent) : InputDevice(inputThread, parent)
{
	d = new KeyboardPrivate();
}

#include "keyboard.moc"
