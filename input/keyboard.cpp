#include "keyboard.h"

using namespace GluonInput;

KeyBoard::KeyBoard(InputThread * inputThread, QObject * parent) : InputDevice(inputThread, parent)
{
}

#include "keyboard.moc"
