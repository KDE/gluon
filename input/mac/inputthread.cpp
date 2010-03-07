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
		d = new InputThreadPrivate();
		d->m_device = pDevice;
		IOHIDDeviceOpen(pDevice,kIOHIDOptionsTypeNone);
		IOHIDDeviceScheduleWithRunLoop( pDevice, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode );
		IOHIDDeviceRegisterInputValueCallback(pDevice, deviceReport, this);
		
		d->m_error = false;
		d->m_msgError = QString();
		d->m_deviceName = "Unknown";
		this->readInformation();
	}

	InputThread::~InputThread()
	{
		IOHIDDeviceClose(d->m_device, kIOHIDOptionsTypeNone);
		CFRelease(d->m_device);
	}
	
	void InputThread::readInformation()
	{
		CFStringRef deviceNameRef = (CFStringRef)IOHIDDeviceGetProperty(d->m_device, CFSTR(kIOHIDProductKey));
		if(CFGetTypeID(deviceNameRef) == CFStringGetTypeID())
		{
			d->m_deviceName = CFStringGetCStringPtr(deviceNameRef, kCFStringEncodingMacRoman);
		}
		
		CFTypeRef type  = IOHIDDeviceGetProperty(d->m_device, CFSTR( kIOHIDVendorIDKey));
		if(type)
		{
			CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &d->m_vendor );
			CFRelease(type);
		}
		else 
		{
			d->m_vendor = -1;
		}
		
		type  = IOHIDDeviceGetProperty(d->m_device, CFSTR( kIOHIDProductIDKey));
		if(type)
		{
			CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &d->m_product );
			CFRelease(type);
		}
		else 
		{
			d->m_product = -1;  
		}
		
		
		type  = IOHIDDeviceGetProperty(d->m_device, CFSTR( kIOHIDTransportKey));
		if(type)
		{
			if(CFGetTypeID(type) == CFNumberGetTypeID())
			{
				CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &d->m_bustype );
				CFRelease(type);            
			}
			else if(CFGetTypeID(type) == CFStringGetTypeID())
			{
				d->m_bustype = -1;
			}
			else 
			{
				d->m_bustype = -1;
			}
			
		}
		
		type = IOHIDDeviceGetProperty(d->m_device, CFSTR( kIOHIDVersionNumberKey));
		if(type)
		{
			CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &d->m_version );
			CFRelease(type);
		}
		else 
		{
			d->m_version = -1;
		}
		
		d->m_buttonCapabilities.clear();
		d->m_absAxisCapabilities.clear();
		d->m_relAxisCapabilities.clear();
		d->m_absAxisInfos.clear();
		
		CFArrayRef elements = IOHIDDeviceCopyMatchingElements(d->m_device, NULL, kIOHIDOptionsTypeNone);
		
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
						d->m_buttonCapabilities.append(usage);
					}
					else if(usagePage == kHIDPage_KeyboardOrKeypad)
					{
						if(usage > 3 && usage <= 231 && !d->m_buttonCapabilities.contains(usage))
							d->m_buttonCapabilities.append(usage);
					}
					else if (usagePage == kHIDPage_GenericDesktop)
					{
						if(usage <= 47 || usage == 60)
							continue;
						
						if(IOHIDElementIsRelative(elementRef))
						{
							d->m_relAxisCapabilities.append(usage);
						}
						else
						{
							d->m_absAxisCapabilities.append(usage);
							AbsVal val(0,0,0,0);
							val.max = (int)IOHIDElementGetLogicalMax(elementRef);
							val.min = (int)IOHIDElementGetLogicalMin(elementRef);
							IOHIDValueRef valRef = NULL;
							IOHIDDeviceGetValue(d->m_device, elementRef, &valRef); 
							val.value = IOHIDValueGetIntegerValue(valRef);
							d->m_absAxisInfos[usage] = val;
							if(usage == kHIDUsage_GD_X)
							{
								d->m_xAbsUsage = usage;
							}
							else if (usage == kHIDUsage_GD_Y)
							{
								d->m_yAbsUsage = usage;
							}
							else if(usage == kHIDUsage_GD_Z)
							{
								d->m_zAbsUsage = usage;
							}
						}
					}
				}
			}
		}
		
		CFRelease(elements);
		
		int deviceUsage = NULL;
		
		type = IOHIDDeviceGetProperty( d->m_device, CFSTR( kIOHIDPrimaryUsageKey));
		
		if(type)
		{
			CFNumberGetValue((CFNumberRef) type, kCFNumberSInt32Type, &deviceUsage);
			CFRelease(type);
		}
		else 
		{
			type = IOHIDDeviceGetProperty( d->m_device, CFSTR( kIOHIDDeviceUsageKey));
			CFNumberGetValue((CFNumberRef) type, kCFNumberSInt32Type, &deviceUsage);
			CFRelease(type);
		}
		
		switch (deviceUsage)
		{
			case GluonInput::KeyBoardDevice:
				d->m_deviceType = GluonInput::KeyBoardDevice;
				break;
			case GluonInput::MouseDevice:
				d->m_deviceType = GluonInput::MouseDevice;
				break;
			case GluonInput::JoystickDevice:
				d->m_deviceType = GluonInput::JoystickDevice;
				break;
			case GluonInput::TabletDevice:
				d->m_deviceType = GluonInput::TabletDevice;
				break;
			case GluonInput::TouchpadDevice:
				d->m_deviceType = GluonInput::TouchpadDevice;
				break;
			default:
				d->m_deviceType = GluonInput::UnknownDevice;
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
		return d->m_xAbsUsage;
	}
	
	int InputThread::getJoystickYAxis()
	{
		return d->m_yAbsUsage;
	}
	
	int InputThread::getJoystickZAxis()
	{
		return d->m_zAbsUsage;
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
		return d->m_vendor;
	}
	
	int InputThread::product()const
	{
		return d->m_product;
	}
	
	int InputThread::version()const
	{
		return d->m_version;
	}
	
	int InputThread::bustype()const
	{
		return d->m_bustype;
	}
	
	QList<int> InputThread::buttonCapabilities()const
	{
		return d->m_buttonCapabilities;
	}
	
	QList<int> InputThread::absAxisCapabilities()const
	{
		return d->m_absAxisCapabilities;
	}
	
	QList<int> InputThread::relAxisCapabilities()const
	{
		return d->m_relAxisCapabilities;
	}
	
	AbsVal InputThread::axisInfo(int axisCode) const
	{
		return d->m_absAxisInfos[axisCode];
	}
	
	const QString InputThread::deviceName() const
	{
		return d->m_deviceName;
	}
	
	GluonInput::DeviceFlag InputThread::deviceType()const
	{
		return d->m_deviceType;
	}
	
	bool InputThread::isEnabled() const
	{
		return this->isRunning();
	}
	
	bool InputThread::error()
	{
		return d->m_error;
	}
	
	QString InputThread::msgError()
	{
		return d->m_msgError;
	}
}

#include "inputthread.moc"