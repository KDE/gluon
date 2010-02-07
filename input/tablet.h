#ifndef TABLET_H
#define TABLET_H

#include "inputdevice.h"

namespace GluonInput
{
	class ThreadAbstract;

	class GLUON_INPUT_EXPORT Tablet : public InputDevice
	{
	public:
		//Tablet(IOHIDDeviceRef device, QObject * parent = 0);
		Tablet(ThreadAbstract * inputThread, QObject * parent = 0);
	};
}
#endif // KCLTABLET_H
