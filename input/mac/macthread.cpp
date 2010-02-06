#include "macthread.h"

#include <QtCore/qeventloop.h>
#include <QtCore/QCoreApplication>
#include "inputevent.h"
#include <IOKit/hid/IOHIDUsageTables.h>
#include "code.h"

namespace GluonInput
{
	/*MacThread::MacThread(IOHIDDeviceRef pDevice, int deviceUsage ,QObject * parent)
	: ThreadAbstract(parent)
	{   
		m_deviceUsage = deviceUsage;
		IOHIDDeviceOpen(pDevice,kIOHIDOptionsTypeNone);
		IOHIDDeviceScheduleWithRunLoop( pDevice, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode );
		IOHIDDeviceRegisterInputValueCallback(pDevice, deviceReport, this);
	}*/
	
	MacThread::MacThread(IOHIDDeviceRef pDevice, QObject * parent)
	: ThreadAbstract(parent)
	{   
		m_device = pDevice;
		IOHIDDeviceOpen(pDevice,kIOHIDOptionsTypeNone);
		IOHIDDeviceScheduleWithRunLoop( pDevice, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode );
		IOHIDDeviceRegisterInputValueCallback(pDevice, deviceReport, this);
	}

	MacThread::~MacThread()
	{
		IOHIDDeviceClose(m_device, kIOHIDOptionsTypeNone);
		CFRelease(m_device);
	}

	/*int MacThread::deviceUsage() const
	{
		return m_deviceUsage;
	}*/

	/*void MacThread::run()
	{
		this->Start();
	}*/
	
	void MacThread::readInformation()
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

	void MacThread::deviceReport(void * inContext, IOReturn inResult, void * inSender, IOHIDValueRef inIOHIDValueRef) 
	{
		IOHIDDeviceRef deviceRef = (IOHIDDeviceRef) inSender;
		MacThread * currentThread = (MacThread* ) inContext;
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
				
				switch (currentThread->deviceUsage())
				{
					case GluonInput::KeyBoardDevice:
						eventType = QEvent::Type(GluonInput::Key);
						break;
					case GluonInput::MouseDevice:
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
	
	void MacThread::setEnabled()
	{
		if(!m_enabled)
		{
			this->run();
			m_enabled = true;
		}
	}
	
	void MacThread::setDisabled()
	{
		if(m_enabled)
		{
			this->stop();
			m_enabled = false;
		}
	}
	
	int MacThread::deviceUsage()
	{
		return m_deviceUsage;
	}
	
	int MacThread::getJoystickXAxis()
	{
		return m_xAbsUsage;
	}
	
	int MacThread::getJoystickYAxis()
	{
		return m_yAbsUsage;
	}
	
	int MacThread::getJoystickZAxis()
	{
		return m_zAbsUsage;
	}
}
#include "macthread.moc"