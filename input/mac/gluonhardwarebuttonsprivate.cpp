#include "gluonhardwarebuttonsprivate.h"

using namespace GluonInput;

GluonHardwareButtonsPrivate::GluonHardwareButtonsPrivate()
{
}

GluonHardwareButtonsPrivate::GluonHardwareButtonsPrivate(GluonHardwareButtonsPrivate& other) : 
	QSharedData(other)
	, keyboardButtonMapping(other.keyboardButtonMapping)
	, mouseButtonMapping(other.mouseButtonMapping)
	, mouseMovementMapping(other.mouseMovementMapping)
	, joystickButtonMapping(other.joystickButtonMapping)
	, joystickMovementMapping(other.joystickMovementMapping)
																								
{
}