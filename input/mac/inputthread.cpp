#include "inputthread.h"

#include <QtCore/qeventloop.h>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <IOKit/hid/IOHIDUsageTables.h>

#include "code.h"
#include "inputthreadprivate.h"
#include "inputbuffer.h"


using namespace GluonInput;

InputThread::InputThread(IOHIDDeviceRef pDevice, QObject * parent)
	: QThread(parent)
{   
	d = new InputThreadPrivate();
	d->device = pDevice;
	IOHIDDeviceOpen(pDevice,kIOHIDOptionsTypeNone);
	IOHIDDeviceScheduleWithRunLoop( pDevice, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode );
	IOHIDDeviceRegisterInputValueCallback(pDevice, deviceReport, this);
	
	d->error = false;
	d->msgError = QString();
	d->deviceName = "Unknown";
	this->readInformation();
}

InputThread::~InputThread()
{
	IOHIDDeviceClose(d->device, kIOHIDOptionsTypeNone);
	CFRelease(d->device);
}

void InputThread::readInformation()
{
	CFStringRef deviceNameRef = (CFStringRef)IOHIDDeviceGetProperty(d->device, CFSTR(kIOHIDProductKey));
	if(CFGetTypeID(deviceNameRef) == CFStringGetTypeID())
	{
		d->deviceName = CFStringGetCStringPtr(deviceNameRef, kCFStringEncodingMacRoman);
	}
	
	CFTypeRef type  = IOHIDDeviceGetProperty(d->device, CFSTR( kIOHIDVendorIDKey));
	if(type)
	{
		CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &d->vendor );
		CFRelease(type);
	}
	else 
	{
		d->vendor = -1;
	}
	
	type  = IOHIDDeviceGetProperty(d->device, CFSTR( kIOHIDProductIDKey));
	if(type)
	{
		CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &d->product );
		CFRelease(type);
	}
	else 
	{
		d->product = -1;  
	}
	
	
	type  = IOHIDDeviceGetProperty(d->device, CFSTR( kIOHIDTransportKey));
	if(type)
	{
		if(CFGetTypeID(type) == CFNumberGetTypeID())
		{
			CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &d->bustype );
			CFRelease(type);            
		}
		else if(CFGetTypeID(type) == CFStringGetTypeID())
		{
			d->bustype = -1;
		}
		else 
		{
			d->bustype = -1;
		}
		
	}
	
	type = IOHIDDeviceGetProperty(d->device, CFSTR( kIOHIDVersionNumberKey));
	if(type)
	{
		CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &d->version );
		CFRelease(type);
	}
	else 
	{
		d->version = -1;
	}
	
	d->buttonCapabilities.clear();
	d->absAxisCapabilities.clear();
	d->relAxisCapabilities.clear();
	d->absAxisInfos.clear();
	
	CFArrayRef elements = IOHIDDeviceCopyMatchingElements(d->device, NULL, kIOHIDOptionsTypeNone);
	
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
					d->buttonCapabilities.append(usage);
				}
				else if(usagePage == kHIDPage_KeyboardOrKeypad)
				{
					if(usage > 3 && usage <= 231 && !d->buttonCapabilities.contains(usage))
						d->buttonCapabilities.append(usage);
				}
				else if (usagePage == kHIDPage_GenericDesktop)
				{
					if(usage <= 47 || usage == 60)
						continue;
					
					if(IOHIDElementIsRelative(elementRef))
					{
						d->relAxisCapabilities.append(usage);
					}
					else
					{
						d->absAxisCapabilities.append(usage);
						AbsVal val(0,0,0,0);
						val.max = (int)IOHIDElementGetLogicalMax(elementRef);
						val.min = (int)IOHIDElementGetLogicalMin(elementRef);
						IOHIDValueRef valRef = NULL;
						IOHIDDeviceGetValue(d->device, elementRef, &valRef); 
						val.value = IOHIDValueGetIntegerValue(valRef);
						d->absAxisInfos[usage] = val;
						if(usage == kHIDUsage_GD_X)
						{
							d->xAbsUsage = usage;
						}
						else if (usage == kHIDUsage_GD_Y)
						{
							d->yAbsUsage = usage;
						}
						else if(usage == kHIDUsage_GD_Z)
						{
							d->zAbsUsage = usage;
						}
					}
				}
			}
		}
	}
	
	CFRelease(elements);
	
	int deviceUsage = NULL;
	
	type = IOHIDDeviceGetProperty( d->device, CFSTR( kIOHIDPrimaryUsageKey));
	
	if(type)
	{
		CFNumberGetValue((CFNumberRef) type, kCFNumberSInt32Type, &deviceUsage);
		CFRelease(type);
	}
	else 
	{
		type = IOHIDDeviceGetProperty( d->device, CFSTR( kIOHIDDeviceUsageKey));
		CFNumberGetValue((CFNumberRef) type, kCFNumberSInt32Type, &deviceUsage);
		CFRelease(type);
	}
	
	switch (deviceUsage)
	{
		case GluonInput::KeyboardDevice:
			d->deviceType = GluonInput::KeyboardDevice;
			break;
		case GluonInput::MouseDevice:
			d->deviceType = GluonInput::MouseDevice;
			break;
		case GluonInput::JoystickDevice:
			d->deviceType = GluonInput::JoystickDevice;
			break;
		case GluonInput::TabletDevice:
			d->deviceType = GluonInput::TabletDevice;
			break;
		/*case GluonInput::TouchpadDevice:
			d->m_deviceType = GluonInput::TouchpadDevice;
			break;*/
		default:
			d->deviceType = GluonInput::UnknownDevice;
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
			
			switch (currentThread->deviceType())
			{
				case GluonInput::KeyboardDevice:
					currentThread->setKeyState(usage, value);
					break;
				case GluonInput::MouseDevice:
					if(usagePage == kHIDPage_GenericDesktop)
					{
						if(value == 0)
							return;
						
#warning set the mouse pos thing here
					}
					else if(usagePage == kHIDPage_Button)
					{
						currentThread->setKeyState(usage, value);
					}
					break;
				case GluonInput::JoystickDevice:
					break;
				case GluonInput::TabletDevice:
					break;
				/*case GluonInput::TouchpadDevice:
					break;*/
				default:
					break;
			}
//#warning remove this and the event class			
/*			CFNumberRef numberRef =  (CFNumberRef)IOHIDDeviceGetProperty(deviceRef,CFSTR(kIOHIDLocationIDKey));
			int id = -1;
			CFNumberGetValue(numberRef, kCFNumberSInt32Type, &id);

			InputEvent * event = new InputEvent(usage, value, eventType);
			QCoreApplication::sendEvent(currentThread->parent(), event);*/
		 }
	}
}

void InputThread::enable()
{
	if(!this->isRunning())
	{
		this->start();
	}
}

void InputThread::disable()
{
	if(this->isRunning())
	{
		this->stop();
	}
}

int InputThread::getJoystickXAxis()
{
	return d->xAbsUsage;
}

int InputThread::getJoystickYAxis()
{
	return d->yAbsUsage;
}

int InputThread::getJoystickZAxis()
{
	return d->zAbsUsage;
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
	return d->vendor;
}

int InputThread::product()const
{
	return d->product;
}

int InputThread::version()const
{
	return d->version;
}

int InputThread::bustype()const
{
	return d->bustype;
}

QList<int> InputThread::buttonCapabilities()const
{
	return d->buttonCapabilities;
}

QList<int> InputThread::absAxisCapabilities()const
{
	return d->absAxisCapabilities;
}

QList<int> InputThread::relAxisCapabilities()const
{
	return d->relAxisCapabilities;
}

AbsVal InputThread::axisInfo(int axisCode) const
{
	return d->absAxisInfos[axisCode];
}

const QString InputThread::deviceName() const
{
	return d->deviceName;
}

GluonInput::DeviceFlag InputThread::deviceType()const
{
	return d->deviceType;
}

bool InputThread::isEnabled() const
{
	return this->isRunning();
}

bool InputThread::error()
{
	return d->error;
}

QString InputThread::msgError()
{
	return d->msgError;
}

void InputThread::setInputBuffer(InputBuffer * buffer)
{
	d->inputBuffer = buffer;
}

void InputThread::setKeyState(int key, bool pressed)
{
	d->inputBuffer->setKeyState(key, pressed);
}

#include "inputthread.moc"