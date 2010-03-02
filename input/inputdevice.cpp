#include "inputdevice.h"

#include <QtCore/QDebug>
#include <QtGui/QApplication>
#include <QtCore/QFile>
#include <QtGui/QMessageBox>
#include <QtGui/QMouseEvent>

#include <core/debughelper.h>

namespace GluonInput
{
	InputDevice::InputDevice(ThreadAbstract * inputThread, QObject * parent)
	: QObject(parent)
	{
		inputListener = inputThread;
		inputListener->setParent(this);
		this->init();
	}

	InputDevice::InputDevice()
	{
		this->init();
	}

	InputDevice::~InputDevice()
	{
		setDisabled();
		delete inputListener;

		qDebug() << "Closed device :" << deviceName();
	}

	void InputDevice::init()
	{
		m_absMove  = false;
		m_relMove = false;
		m_lastAbsAxis = 0;
		m_lastRelAxis = 0;
	}

	int InputDevice::vendor()const
	{
		return inputListener->vendor();
	}

	int InputDevice::product()const
	{
		return inputListener->product();
	}

	int InputDevice::version()const
	{
		return inputListener->version();
	}

	int InputDevice::bustype()const
	{
		return inputListener->bustype();
	}

	const QString InputDevice::deviceName() const
	{
		//return m_deviceName;
		return inputListener->deviceName();
	}

	GluonInput::DeviceFlag InputDevice::deviceType()const
	{
		//return m_deviceType;
		return inputListener->deviceType();
	}

	bool InputDevice::button(int code)const
	{
		return m_buttons.contains(code);
	}

	int InputDevice::anyPress() const
	{
		if (m_buttons.size() > 0)
		{
			return m_buttons.last();
		} else {
			return 0;
		}
	}

	bool InputDevice::anyAbsMove()
	{
		if (m_absMove)
		{
			m_absMove = false;
			return true;
		}
		return false;
	}

	bool InputDevice::anyRelMove()
	{
		if (m_relMove)
		{
			m_relMove = false;
			return true;
		}
		return false;
	}

	int InputDevice::lastAbsAxis()const
	{
		return m_lastAbsAxis;
	}

	int InputDevice::lastRelAxis()const
	{
		return m_lastRelAxis;
	}

	int InputDevice::relAxisValue(int code)const
	{
		if (m_relAxis.contains(code))
		{
			return m_relAxis[code];
		} else {
			return 0;
		}
	}

	int InputDevice::absAxisValue(int code)const
	{
		if (m_absAxis.contains(code))
		{
			return m_absAxis[code];
		} else {
			return 0;
		}
	}

	QList<int> InputDevice::buttonCapabilities()const
	{
		return inputListener->buttonCapabilities();
	}

	QList<int> InputDevice::absAxisCapabilities()const
	{
		return inputListener->absAxisCapabilities();
	}

	QList<int> InputDevice::relAxisCapabilities()const
	{
		return inputListener->relAxisCapabilities();
	}

	AbsVal InputDevice::axisInfo(int axisCode)const
	{
		return inputListener->axisInfo(axisCode);
	}

	bool InputDevice::error()const
	{
		return inputListener->error();
	}

	QString InputDevice::msgError()const
	{
		return inputListener->msgError();
	}

	bool InputDevice::isEnabled() const
	{
		return inputListener->isEnabled();
	}


	bool InputDevice::event(QEvent * evt)
	{
        DEBUG_FUNC_NAME
		InputEvent * event = (InputEvent*)evt;
		emit eventSent(event);

		switch (event->type())
		{
			case GluonInput::Key:

				if (event->value() == 1)
				{ // if click
					m_buttons.append(event->code());
					emit buttonPressed(event->code());
					emit pressed();
				}

				if (event->value() == 0)
				{ //if release
					m_buttons.removeOne(event->code());
					emit buttonReleased(event->code());
				}
				return true;
				break;

			case GluonInput::RelativeAxis:
				emit moved();
				m_relMove = true;
				m_lastRelAxis = event->code();
				m_relAxis[event->code()] = event->value();
				emit relAxisChanged(event->code(), event->value());
				return true;
				break;

			case GluonInput::AbsoluAxis:
				emit moved();
				m_absMove = true;
				m_lastAbsAxis = event->code();
				m_absAxis[event->code()] = event->value();
				emit absAxisChanged(event->code(), event->value());
				return true;
				break;

			default:
			  qDebug() << "nothing at all " << event->type();
				break;
		}

		return QObject::event(evt);
	}

	void InputDevice::setEnabled()
	{
		inputListener->setEnabled();
	}

	void InputDevice::setDisabled()
	{
		inputListener->setDisabled();
		m_buttons.clear();
		m_relAxis.clear();
		m_absAxis.clear();
		m_relMove = false;
		m_absMove = false;
	}
}

#include "inputdevice.moc"
