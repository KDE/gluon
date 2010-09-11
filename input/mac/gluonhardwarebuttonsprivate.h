#ifndef GLUONHARDWAREBUTTONSPRIVATE_H
#define GLUONHARDWAREBUTTONSPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QHash>

namespace GluonInput
{
	class GluonHardwareButtonsPrivate : public QSharedData {
		
		public:
			GluonHardwareButtonsPrivate();
		
			GluonHardwareButtonsPrivate(GluonHardwareButtonsPrivate& other);
			
			QHash<int, int> keyboardButtonMapping;
			QHash<int, int> mouseButtonMapping;
			QHash<int, int> mouseAxisMapping;
			QHash<int, int> joystickButtonMapping;
			QHash<int, int> joystickAxisMapping;
	};
}

#endif