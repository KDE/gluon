#ifndef MOUSE_H
#define MOUSE_H

#include "inputdevice.h"

#include <QtCore/QList>
#include <QtCore/QPoint>
#include <QtGui/QWidget>

namespace GluonInput
{
	class ThreadAbstract;

	class GLUON_INPUT_EXPORT Mouse : public InputDevice
	{
		Q_OBJECT

	public:
		//Mouse(IOHIDDeviceRef device, QObject * parent = 0);
		Mouse(ThreadAbstract * inputThread, QObject * parent = 0);

		QPoint position();
		void setSensibility(double s);
		void setOrigin(const QPoint p);
		int wheelPosition() const;
		int hWheelPosition()const;
		double sensibility()const;

	private:
		QPoint m_position;
		QPoint m_originalPosition;
		double m_sensibility;
	};
}
//@}
#endif // KCLMOUSE_H
