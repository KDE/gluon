#include "tablet.h"

namespace GluonInput
{	
	Tablet::Tablet(InputThread * inputThread, QObject * parent) : InputDevice(inputThread, parent)
	{
		d = new TabletPrivate();
	}
}
