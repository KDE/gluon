#include "keyboard.h"

using namespace GluonInput;

KeyBoard::KeyBoard(InputThread * inputThread, QObject * parent) : InputDevice(inputThread, parent)
{
	d = new KeyBoardPrivate();
}

#include "keyboard.moc"
