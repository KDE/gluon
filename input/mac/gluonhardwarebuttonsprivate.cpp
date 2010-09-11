#include "gluonhardwarebuttonsprivate.h"

using namespace GluonInput;

GluonHardwareButtonsPrivate::GluonHardwareButtonsPrivate()
{
}

GluonHardwareButtonsPrivate::GluonHardwareButtonsPrivate(GluonHardwareButtonsPrivate& other) : 
	QSharedData(other)
	, keyboardButtonMapping(other.keyboardButtonMapping)
	, mouseButtonMapping(other.mouseButtonMapping)
	, mouseAxisMapping(other.mouseAxisMapping)
	, joystickButtonMapping(other.joystickButtonMapping)
	, joystickAxisMapping(other.joystickAxisMapping)
																								
{
}