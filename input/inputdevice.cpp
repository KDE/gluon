#include "inputdevice.h"

#include <QtCore/QDebug>
#include <QtGui/QApplication>
#include <QtCore/QFile>
#include <QtGui/QMessageBox>
#include <QtGui/QMouseEvent>

#include <core/debughelper.h>

namespace GluonInput
{
	/*InputDevice::InputDevice(IOHIDDeviceRef device, QObject * parent)
	: QObject(parent)
	{
		this->init();

		m_device = device;
		readInformation();
		inputListener = new ThreadAbstract(m_device, m_deviceType, this);
	}*/

	InputDevice::InputDevice(ThreadAbstract * inputThread, QObject * parent)
	: QObject(parent)
	{
		inputListener = inputThread;
		this->init();
	}

	InputDevice::InputDevice()
	{
		this->init();
	}

	InputDevice::~InputDevice()
	{
		setDisabled();
		//IOHIDDeviceClose(m_device, kIOHIDOptionsTypeNone);
		//CFRelease(m_device);
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
		//return m_vendor;
		return inputListener->vendor();
	}

	int InputDevice::product()const
	{
		//return m_product;
		return inputListener->product();
	}

	int InputDevice::version()const
	{
		//return m_version;
		return inputListener->version();
	}

	int InputDevice::bustype()const
	{
		//return m_bustype;
		return inputListener->bustype();
	}

	/*const IOHIDDeviceRef InputDevice::device()const
	{
		return m_device;
	}*/

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
		//return m_buttonCapabilities;
		return inputListener->buttonCapabilities();
	}

	QList<int> InputDevice::absAxisCapabilities()const
	{
		//return m_absAxisCapabilities;
		return inputListener->absAxisCapabilities();
	}

	QList<int> InputDevice::relAxisCapabilities()const
	{
		//return m_relAxisCapabilities;
		return inputListener->relAxisCapabilities();
	}

	AbsVal InputDevice::axisInfo(int axisCode)const
	{
		//return m_absAxisInfos[axisCode];
		return inputListener->axisInfo(axisCode);
	}

	bool InputDevice::error()const
	{
		//return m_error;
		return inputListener->error();
	}

	QString InputDevice::msgError()const
	{
		//return m_msgError;
		return inputListener->msgError();
	}

	bool InputDevice::isEnabled() const
	{
		//return m_enable;
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
				break;
		}

		return QObject::event(evt);
	}


	/*void InputDevice::readInformation()
	{
		CFStringRef deviceNameRef = (CFStringRef)IOHIDDeviceGetProperty(m_device, CFSTR(kIOHIDProductKey));
		if(CFGetTypeID(deviceNameRef) == CFStringGetTypeID())
		{
			m_deviceName = CFStringGetCStringPtr(deviceNameRef, kCFStringEncodingMacRoman);
		}

		CFTypeRef type  = IOHIDDeviceGetProperty(m_device, CFSTR( kIOHIDVendorIDKey));
		if(type)
		{
			CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &m_vendor );
			CFRelease(type);
		}
		else
		{
			m_vendor = -1;
		}

		type  = IOHIDDeviceGetProperty(m_device, CFSTR( kIOHIDProductIDKey));
		if(type)
		{
			CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &m_product );
			CFRelease(type);
		}
		else
		{
			m_product = -1;
		}


		type  = IOHIDDeviceGetProperty(m_device, CFSTR( kIOHIDTransportKey));
		if(type)
		{
			if(CFGetTypeID(type) == CFNumberGetTypeID())
			{
				CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &m_bustype );
				CFRelease(type);
			}
			else if(CFGetTypeID(type) == CFStringGetTypeID())
			{
				m_bustype = -1;
			}
			else
			{
				m_bustype = -1;
			}

		}

		type = IOHIDDeviceGetProperty(m_device, CFSTR( kIOHIDVersionNumberKey));
		if(type)
		{
			CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &m_version );
			CFRelease(type);
		}
		else
		{
			m_version = -1;
		}

		m_buttonCapabilities.clear();
		m_absAxisCapabilities.clear();
		m_relAxisCapabilities.clear();
		m_absAxisInfos.clear();

		CFArrayRef elements = IOHIDDeviceCopyMatchingElements(m_device, NULL, kIOHIDOptionsTypeNone);

		if(elements)
		{
			for(int i = 0; i < CFArrayGetCount(elements); i++)
			{
				IOHIDElementRef elementRef = (IOHIDElementRef)CFArrayGetValueAtIndex(elements,(CFIndex)i);
				if(CFGetTypeID(elementRef) == IOHIDElementGetTypeID())
				{
					int usagePage = IOHIDElementGetUsagePage( elementRef );
					int usage = IOHIDElementGetUsage( elementRef );

					if(usagePage == kHIDPage_Button)
					{
						m_buttonCapabilities.append(usage);
					}
					else if(usagePage == kHIDPage_KeyboardOrKeypad)
					{
						if(usage > 3 && usage <= 231 && !m_buttonCapabilities.contains(usage))
							m_buttonCapabilities.append(usage);
					}
					else if (usagePage == kHIDPage_GenericDesktop)
					{
						if(usage <= 47 || usage == 60)
							continue;

						if(IOHIDElementIsRelative(elementRef))
						{
							m_relAxisCapabilities.append(usage);
						}
						else
						{
							m_absAxisCapabilities.append(usage);
							AbsVal val(0,0,0,0);
							val.max = (int)IOHIDElementGetLogicalMax(elementRef);
							val.min = (int)IOHIDElementGetLogicalMin(elementRef);
							IOHIDValueRef valRef = NULL;
							IOHIDDeviceGetValue(m_device, elementRef, &valRef);
							val.value = IOHIDValueGetIntegerValue(valRef);
							m_absAxisInfos[usage] = val;
							if(usage == kHIDUsage_GD_X)
							{
								m_xAbsUsage = usage;
							}
							else if (usage == kHIDUsage_GD_Y)
							{
								m_yAbsUsage = usage;
							}
							else if(usage == kHIDUsage_GD_Z)
							{
								m_zAbsUsage = usage;
							}
						}
					}
				}
			}
		}

		CFRelease(elements);

		int deviceUsage = NULL;

		type = IOHIDDeviceGetProperty( m_device, CFSTR( kIOHIDPrimaryUsageKey));

		if(type)
		{
			CFNumberGetValue((CFNumberRef) type, kCFNumberSInt32Type, &deviceUsage);
			CFRelease(type);
		}
		else
		{
			type = IOHIDDeviceGetProperty( m_device, CFSTR( kIOHIDDeviceUsageKey));
			CFNumberGetValue((CFNumberRef) type, kCFNumberSInt32Type, &deviceUsage);
			CFRelease(type);
		}

		switch (deviceUsage)
		{
			case GluonInput::KeyBoardDevice:
				m_deviceType = GluonInput::KeyBoardDevice;
				break;
			case GluonInput::MouseDevice:
				m_deviceType = GluonInput::MouseDevice;
				break;
			case GluonInput::JoystickDevice:
				m_deviceType = GluonInput::JoystickDevice;
				break;
			case GluonInput::TabletDevice:
				m_deviceType = GluonInput::TabletDevice;
				break;
			case GluonInput::TouchpadDevice:
				m_deviceType = GluonInput::TouchpadDevice;
				break;
			default:
				m_deviceType = GluonInput::UnknownDevice;
				break;
		}
	}*/

	void InputDevice::setEnabled()
	{
		inputListener->setEnabled();
		/*m_enable = true;
		if (!error())
		{
			if(inputListener != NULL)
			{
				inputListener->terminate();
				delete inputListener;
			}
			inputListener = new Thread(m_device, m_deviceType,this);
			inputListener->start();
		}*/
	}

	void InputDevice::setDisabled()
	{
		//m_enable = false;
		inputListener->setDisabled();
		m_buttons.clear();
		m_relAxis.clear();
		m_absAxis.clear();
		m_relMove = false;
		m_absMove = false;
		//inputListener->terminate();
		//delete inputListener;
	}

	/*const QString InputDevice::devicePath() const
	{
		return "Unknown";
	}*/
}

#include "inputdevice.moc"
