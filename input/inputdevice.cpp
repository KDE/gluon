#include "inputdevice.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaEnum>

#include "absval.h"
#include "inputdeviceprivate.h"
#include "inputbuffer.h"
#include "gluondevices.h"

#include <core/debughelper.h>

using namespace GluonInput;

InputDevice::InputDevice(InputThread * inputThread, QObject * parent)
	: QObject(parent)
{
	d = new InputDevicePrivate();
	d->inputThread = inputThread;
	d->inputThread->setParent(this);	
	d->inputBuffer = new InputBuffer();
	d->inputBuffer->setParent(this);
	this->init();
	
	connect(inputThread, SIGNAL(buttonStateChanged(int, int)), this, SLOT(buttonStateChanged(int, int)), Qt::DirectConnection);
}

InputDevice::InputDevice()
{
	this->init();
}

InputDevice::~InputDevice()
{
	this->setEnabled(false);
	delete d->inputThread;
	delete d->inputBuffer;

	qDebug() << "Closed device :" << deviceName();
}

void InputDevice::init()
{
	d->m_absMove  = false;
	d->m_relMove = false;
	d->m_lastAbsAxis = 0;
	d->m_lastRelAxis = 0;
}

int InputDevice::vendor()const
{
	return d->inputThread->vendor();
}

int InputDevice::product()const
{
	return d->inputThread->product();
}

int InputDevice::version()const
{
	return d->inputThread->version();
}

int InputDevice::bustype()const
{
	return d->inputThread->bustype();
}

const QString InputDevice::deviceName() const
{
	return d->inputThread->deviceName();
}

GluonInput::DeviceFlag InputDevice::deviceType()const
{
	return d->inputThread->deviceType();
}

bool InputDevice::button(int code)const
{
	return d->m_buttons.contains(code);
}

/*bool InputDevice::anyAbsMove()
{
	if (d->m_absMove)
	{
		d->m_absMove = false;
		return true;
	}
	return false;
}

bool InputDevice::anyRelMove()
{
	if (d->m_relMove)
	{
		d->m_relMove = false;
		return true;
	}
	return false;
}

int InputDevice::lastAbsAxis()const
{
	return d->m_lastAbsAxis;
}

int InputDevice::lastRelAxis()const
{
	return d->m_lastRelAxis;
}

int InputDevice::relAxisValue(int code)const
{
	if (d->m_relAxis.contains(code))
	{
		return d->m_relAxis[code];
	} else {
		return 0;
	}
}

int InputDevice::absAxisValue(int code)const
{
	if (d->m_absAxis.contains(code))
	{
		return d->m_absAxis[code];
	} else {
		return 0;
	}
}*/

QList<int> InputDevice::buttonCapabilities()const
{
	return d->inputThread->buttonCapabilities();
}

QList<int> InputDevice::absAxisCapabilities()const
{
	return d->inputThread->absAxisCapabilities();
}

QList<int> InputDevice::relAxisCapabilities()const
{
	return d->inputThread->relAxisCapabilities();
}

AbsVal InputDevice::axisInfo(int axisCode)const
{
	return d->inputThread->axisInfo(axisCode);
}

bool InputDevice::error()const
{
	return d->inputThread->error();
}

QString InputDevice::msgError()const
{
	return d->inputThread->msgError();
}

bool InputDevice::isEnabled() const
{
	return d->inputThread->isEnabled();
}

void InputDevice::setEnabled(bool enable)
{
  if(enable && !d->inputThread->isEnabled())
  {
	d->inputThread->start();
  }
  else if (!enable && d->inputThread->isEnabled())
  {
	d->inputThread->stop();
  }
}

void InputDevice::setInputThread(InputThread * inputThread)
{
	d->inputThread->stop();
	delete d->inputThread;
	d->inputThread = inputThread;
}

InputThread * InputDevice::inputThread() const
{
	return d->inputThread;
}

bool InputDevice::buttonPressed(int code) const
{
	return d->inputBuffer->buttonState(code);
}

QString InputDevice::buttonName(int code) const
{
	return GluonButtons::instance()->buttonName(this->deviceType(), code);
}

QString InputDevice::axisName(int code) const
{
	switch (this->deviceType())
	{
		case MouseDevice:
		case JoystickDevice:
			return GluonButtons::instance()->axisName(this->deviceType(), code);
			break;
		default:
			return "Unknown";
			break;
	}		
}

void InputDevice::buttonStateChanged(int code, int value)
{
	d->inputBuffer->setButtonState(code, value);
}
/*
bool InputDevice::event(QEvent * evt)
    {
        InputEvent * event = (InputEvent*)evt;
        emit eventSent(event);

        switch (event->type())
        {
            case GluonInput::Key:

                if (event->value() == 1)
                { // if click
                    d->m_buttons.append(event->code());
                    emit buttonPressed(event->code());
                    emit pressed();
                }

                if (event->value() == 0)
                { //if release
                    d->m_buttons.removeOne(event->code());
                    emit buttonReleased(event->code());
                }
                return true;
                break;

            case GluonInput::RelativeAxis:
                emit moved();
                d->m_relMove = true;
                d->m_lastRelAxis = event->code();
                d->m_relAxis[event->code()] = event->value();
                emit relAxisChanged(event->code(), event->value());
                return true;
                break;

            case GluonInput::AbsoluAxis:
                emit moved();
                d->m_absMove = true;
                d->m_lastAbsAxis = event->code();
                d->m_absAxis[event->code()] = event->value();
                emit absAxisChanged(event->code(), event->value());
                return true;
                break;

            default:
                break;
        }

        return QObject::event(evt);
    }
*/
#include "inputdevice.moc"
