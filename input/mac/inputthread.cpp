#include "inputthread.h"

#include <QtCore/qeventloop.h>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include "inputevent.h"
#include <IOKit/hid/IOHIDUsageTables.h>
#include "code.h"

namespace GluonInput
{	
	InputThread::InputThread(IOHIDDeviceRef pDevice, QObject * parent)
	: QThread(parent)
	{   
		m_device = pDevice;
		IOHIDDeviceOpen(pDevice,kIOHIDOptionsTypeNone);
		IOHIDDeviceScheduleWithRunLoop( pDevice, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode );
		IOHIDDeviceRegisterInputValueCallback(pDevice, deviceReport, this);
		
		m_error = false;
		m_msgError = QString();
		m_deviceName = "Unknown";
		this->readInformation();
	}

	InputThread::~InputThread()
	{
		IOHIDDeviceClose(m_device, kIOHIDOptionsTypeNone);
		CFRelease(m_device);
	}
	
	void InputThread::readInformation()
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
	}

	void InputThread::deviceReport(void * inContext, IOReturn inResult, void * inSender, IOHIDValueRef inIOHIDValueRef) 
	{
		IOHIDDeviceRef deviceRef = (IOHIDDeviceRef) inSender;
		InputThread * currentThread = (InputThread* ) inContext;
		if(inResult == kIOReturnSuccess && CFGetTypeID(deviceRef) == IOHIDDeviceGetTypeID())
		{
			IOHIDElementRef elementRef = IOHIDValueGetElement(inIOHIDValueRef);
			
			int usagePage = IOHIDElementGetUsagePage( elementRef );
			int usage = IOHIDElementGetUsage( elementRef );
			int value = IOHIDValueGetIntegerValue(inIOHIDValueRef);
				
			if(usagePage == kHIDPage_GenericDesktop || usagePage == kHIDPage_KeyboardOrKeypad || usagePage == kHIDPage_Button)
			{
				if(usagePage == kHIDPage_GenericDesktop && usage == 60)
					return;
				else if(usagePage == kHIDPage_KeyboardOrKeypad && (usage <= 3 || usage > 231))
					return;
				
				QEvent::Type eventType;
				
				switch (currentThread->deviceType())
				{
					case GluonInput::KeyBoardDevice:
						eventType = QEvent::Type(GluonInput::Key);
						break;
					case GluonInput::MouseDevice:
#warning fix such that, mouse buttons return 0,1,2 and so forth. Atm. it is using the same buttonname as keyboard
						if(usagePage == kHIDPage_GenericDesktop)
						{
							eventType = QEvent::Type(GluonInput::RelativeAxis);
						}
						else if(usagePage == kHIDPage_Button)
						{
							eventType = QEvent::Type(GluonInput::Key);
						}
						break;
					case GluonInput::JoystickDevice:
						break;
					case GluonInput::TabletDevice:
						break;
					case GluonInput::TouchpadDevice:
						break;
					default:
						break;
				}
				
				CFNumberRef numberRef =  (CFNumberRef)IOHIDDeviceGetProperty(deviceRef,CFSTR(kIOHIDLocationIDKey));
				int id = -1;
				CFNumberGetValue(numberRef, kCFNumberSInt32Type, &id);
				InputEvent * event = new InputEvent(usage, value, eventType);
				QCoreApplication::sendEvent(currentThread->parent(), event);
			 }
		}
	}
	
	void InputThread::setEnabled()
	{
		if(!this->isRunning())
		{
			this->start();
		}
	}
	
	void InputThread::setDisabled()
	{
		if(this->isRunning())
		{
			this->stop();
		}
	}
	
	int InputThread::getJoystickXAxis()
	{
		return m_xAbsUsage;
	}
	
	int InputThread::getJoystickYAxis()
	{
		return m_yAbsUsage;
	}
	
	int InputThread::getJoystickZAxis()
	{
		return m_zAbsUsage;
	}
	
	void InputThread::run()
	{
		this->exec();
	}
	
	void InputThread::stop()
	{
		this->quit();
	}
	
	int InputThread::vendor()const
	{
		return m_vendor;
	}
	
	int InputThread::product()const
	{
		return m_product;
	}
	
	int InputThread::version()const
	{
		return m_version;
	}
	
	int InputThread::bustype()const
	{
		return m_bustype;
	}
	
	QList<int> InputThread::buttonCapabilities()const
	{
		return m_buttonCapabilities;
	}
	
	QList<int> InputThread::absAxisCapabilities()const
	{
		return m_absAxisCapabilities;
	}
	
	QList<int> InputThread::relAxisCapabilities()const
	{
		return m_relAxisCapabilities;
	}
	
	AbsVal InputThread::axisInfo(int axisCode) const
	{
		return m_absAxisInfos[axisCode];
	}
	
	const QString InputThread::deviceName() const
	{
		return m_deviceName;
	}
	
	GluonInput::DeviceFlag InputThread::deviceType()const
	{
		return m_deviceType;
	}
	
	bool InputThread::isEnabled() const
	{
		return this->isRunning();
	}
	
	bool InputThread::error()
	{
		return m_error;
	}
	
	QString InputThread::msgError()
	{
		return m_msgError;
	}
}

#include "inputthread.moc"