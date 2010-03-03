#include "mouse.h"

#include <QtCore/QDebug>

namespace GluonInput
{
	Mouse::Mouse(InputThread * inputThread, QObject * parent) : InputDevice(inputThread, parent)
	{
		m_originalPosition = QPoint(0, 0);
		m_position = m_originalPosition;
		m_sensibility = 1;
	}

	QPoint Mouse::position()
	{
		if ( anyRelMove())
		{
		  m_position += QPoint(relAxisValue(lastRelAxis()), relAxisValue(lastRelAxis()));
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
	  return relAxisValue(lastRelAxis());
	}

	int Mouse::hWheelPosition()const 
	{
	  return relAxisValue(lastRelAxis());
	}

	double Mouse::sensibility()const
	{
		return m_sensibility;
	}
}
#include "mouse.moc"
