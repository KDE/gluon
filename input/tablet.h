#ifndef TABLET_H
#define TABLET_H

#include "inputdevice.h"
#include "tabletprivate.h"
#include <QtCore/QSharedData>

namespace GluonInput
{
	class InputThread;

	class GLUON_INPUT_EXPORT Tablet : public InputDevice
	{
	public:
		Tablet(InputThread * inputThread, QObject * parent = 0);
		
	private:
		QSharedDataPointer<TabletPrivate> d;
	};
}
#endif // KCLTABLET_H
