#include "joystick.h"
#include "joystickprivate.h"

using namespace GluonInput;

Joystick::Joystick(InputThread * inputThread, QObject * parent) : InputDevice(inputThread, parent)
{
	d = new JoystickPrivate();
	
	connect(inputThread, SIGNAL(absAxisMoved(int, int)), this, SLOT(joystickMoved(int, int)));
}

int Joystick::axisX() const
{
	return absAxisValue(this->inputThread()->getJoystickXAxis());
}

int Joystick::axisY()const
{
	return absAxisValue(this->inputThread()->getJoystickYAxis());
}

int Joystick::axisZ() const
{
	return absAxisValue(this->inputThread()->getJoystickZAxis());
}

void Joystick::joystickMoved(int axis, int distance)
{

}

#include "joystick.moc"
