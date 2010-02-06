#include "mouse.h"

#include <QtCore/QDebug>

namespace GluonInput
{
	/*Mouse::Mouse(IOHIDDeviceRef device, QObject *parent)
			: InputDevice(device, parent)
	{
		m_originalPosition = QPoint(0, 0);
		m_position = m_originalPosition;
		m_sensibility = 1;
	}*/
	Mouse::Mouse(ThreadAbstract * inputThread, QObject * parent) : InputDevice(inputThread, parent)
	{
		m_originalPosition = QPoint(0, 0);
		m_position = m_originalPosition;
		m_sensibility = 1;
	}

	QPoint Mouse::position()
	{
		if ( anyRelMove())
		{
			m_position += QPoint(relAxisValue(m_lastRelAxis), relAxisValue(m_lastRelAxis));
		}
		return (m_position+m_originalPosition)*m_sensibility;
	}

	void Mouse::setSensibility(double s)
	{
		m_sensibility=s;
	}

	void Mouse::setOrigin(const QPoint p) 
	{
		m_originalPosition = p;
	}

	int Mouse::wheelPosition() const
	{
		return relAxisValue(m_lastRelAxis);
	}

	int Mouse::hWheelPosition()const 
	{
		return relAxisValue(m_lastRelAxis);
	}

	double Mouse::sensibility()const
	{
		return m_sensibility;
	}
}
#include "mouse.moc"
