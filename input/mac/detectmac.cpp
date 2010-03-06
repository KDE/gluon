#include "detectmac.h"

#include "gluon_input_export.h"
#include "inputdefinitions.h"

#include <QtCore/QDebug>
#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDUsageTables.h>
#include "inputthread.h"

namespace GluonInput
{
	DetectMac::DetectMac(QObject * parent)
	: Detect(parent)
	{
		deviceManager = NULL;
		devices = NULL;
	}

	DetectMac::~DetectMac()
	{
		CFRelease(deviceManager);
		CFRelease(devices);
	}

	void DetectMac::searchDevice()
	{
		qDebug() << "Checking if deviceManager exists";
		if(deviceManager == NULL)
		{
			qDebug() << "Creating device manager";
			deviceManager = IOHIDManagerCreate( kCFAllocatorDefault, kIOHIDOptionsTypeNone);
		}
		
		CFMutableDictionaryRef dict;
		CFMutableArrayRef matchingArray = CFArrayCreateMutable( kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks );
		//keyboard
		dict = createMatchingDictionary(kHIDPage_GenericDesktop, kHIDUsage_GD_Keyboard);
		if(dict)
		{
			CFArrayAppendValue(matchingArray, dict);
			CFRelease(dict);
		}
		//mouse
		dict = createMatchingDictionary(kHIDPage_GenericDesktop, kHIDUsage_GD_Mouse);
		if(dict)
		{
			CFArrayAppendValue(matchingArray, dict);
			CFRelease(dict);
		}
		//joystick
		dict = createMatchingDictionary(kHIDPage_GenericDesktop, kHIDUsage_GD_Joystick);
		if(dict)
		{
			CFArrayAppendValue(matchingArray, dict);
			CFRelease(dict);
		}
		//digitizer / tablet
		dict = createMatchingDictionary(kHIDPage_Digitizer, kHIDUsage_Dig_Digitizer);
		if(dict)
		{
			CFArrayAppendValue(matchingArray, dict);
			CFRelease(dict);
		}   
		//touchpad
		dict = createMatchingDictionary(kHIDPage_Digitizer, kHIDUsage_Dig_TouchPad);
		if(dict)
		{
			CFArrayAppendValue(matchingArray, dict);
			CFRelease(dict);
		}   
		
		if ( CFGetTypeID( deviceManager ) == IOHIDManagerGetTypeID( ) ) 
		{
			IOHIDManagerSetDeviceMatchingMultiple(deviceManager, matchingArray);
			
			if(IOHIDManagerOpen(deviceManager, kIOHIDOptionsTypeNone) == kIOReturnSuccess)
			{
				devices = IOHIDManagerCopyDevices(deviceManager);
				
				if(CFSetGetCount(devices) > 0)
				{               
					CFSetApplyFunction(devices, createDevices, this);
				}
			}        
		}
	}

	QList<InputDevice *> DetectMac::getInputList() 
	{
		return m_inputList;
	}

	QList<KeyBoard *> DetectMac::getKeyboardList() 
	{
		return m_keyboardList;
	}

	QList<Mouse *> DetectMac::getMouseList() 
	{
		return m_mouseList;
	}

	QList<Joystick *> DetectMac::getJoystickList() 
	{
		return m_joystickList;
	}

	QList<Tablet *> DetectMac::getTabletList() 
	{
		return m_tabletList;
	}

	QList<InputDevice *> DetectMac::getUnknownDeviceList() 
	{
		return m_unknownList;
	}


	void DetectMac::addInput(InputDevice *i) 
	{
		m_inputList.append(i);
	}

	void DetectMac::addKeyboard(InputDevice *i)
	{
		KeyBoard * keybd = (KeyBoard*) i;
		//keybd->setEnabled();
		m_keyboardList.append(keybd);
		m_inputList.append(i);
	}

	void DetectMac::addMouse(InputDevice *i) 
	{
		Mouse * mouse = (Mouse*) i;
		//mouse->setEnabled();
		m_mouseList.append(mouse);
		m_inputList.append(i);
	}

	void DetectMac::addJoystick(InputDevice *i)
	{
		Joystick * joy = (Joystick*) i;
		//joy->setEnabled();
		m_joystickList.append(joy);
		m_inputList.append(i);
	}

	void DetectMac::addTablet(InputDevice *i) 
	{
		Tablet * tablet = (Tablet*) i;
		//tablet->setEnabled();
		m_tabletList.append(tablet);
		m_inputList.append(i);
	}

	void DetectMac::addUnknown(InputDevice *i) 
	{
		m_unknownList.append(i);
		m_inputList.append(i);
	}

	void DetectMac::clear()
	{
		m_inputList.clear();
		m_keyboardList.clear();
		m_mouseList.clear();
		m_joystickList.clear();
		m_tabletList.clear();
		m_unknownList.clear();
	}

	void DetectMac::setAllEnabled()
	{
		qDebug() << "Enabling all devices";
		foreach(InputDevice *input, this->getInputList()) {
			input->setEnabled();
		}
	}

	void DetectMac::setAllDisabled()
	{
		foreach(InputDevice *input, this->getInputList()) {
			input->setDisabled();
		}
	}   

	void DetectMac::createDevices(const void *value, void *context)
	{
		IOHIDDeviceRef device = (IOHIDDeviceRef) value;
		DetectMac* detect = (DetectMac*) context;
		
		if ( CFGetTypeID( device ) == IOHIDDeviceGetTypeID( ) ) 
		{
			IOHIDDeviceOpen(device,kIOHIDOptionsTypeNone);
			
			int usagePage = NULL;
			int usage = NULL; 
			
			CFTypeRef type = IOHIDDeviceGetProperty( device, CFSTR( kIOHIDDeviceUsagePageKey ) );
			
			if ( type ) 
			{
				// if this is a number
				if ( CFNumberGetTypeID() == CFGetTypeID( type ) ) 
				{
					// get it's value
					CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &usagePage );
				}
				CFRelease(type);
			}
			
			type = IOHIDDeviceGetProperty( device, CFSTR( kIOHIDDeviceUsageKey ) );
			
			if ( type ) 
			{
				// if this is a number
				if ( CFNumberGetTypeID() == CFGetTypeID( type ) ) 
				{
					// get it's value
					CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &usage );
				}
				CFRelease(type);
			}
			
			if(!usage || !usagePage)
			{
				type = IOHIDDeviceGetProperty( device, CFSTR( kIOHIDPrimaryUsagePageKey ) );
				
				if ( type ) 
				{
					// if this is a number
					if ( CFNumberGetTypeID() == CFGetTypeID( type ) ) 
					{
						// get it's value
						CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &usagePage );
					}
					CFRelease(type);
				}
				
				type = IOHIDDeviceGetProperty( device, CFSTR( kIOHIDPrimaryUsageKey ) );

				if ( type ) 
				{
					// if this is a number
					if ( CFNumberGetTypeID() == CFGetTypeID( type ) ) 
					{
						// get it's value
						CFNumberGetValue( ( CFNumberRef ) type, kCFNumberSInt32Type, &usage );
					}
					CFRelease(type);
				}
				
			}
			
			if(!usage || !usagePage)
			{
				usagePage = 0;
			}

			
			InputDevice* inputDevice;
			if(usagePage == kHIDPage_GenericDesktop)
			{
				switch (usage) 
				{
					case GluonInput::KeyBoardDevice:
						inputDevice = new KeyBoard(new InputThread(device));
						detect->addKeyboard(inputDevice);
						break;
					case GluonInput::MouseDevice:
						inputDevice = new Mouse(new InputThread(device));
						detect->addMouse(inputDevice);
						break;
					case GluonInput::JoystickDevice:
						inputDevice = new Joystick(new InputThread(device));
						detect->addJoystick(inputDevice);
						break;
					default:
						inputDevice = new InputDevice(new InputThread(device));
						detect->addUnknown(inputDevice);
						break;
				}
			}
			else if(usagePage == kHIDPage_Digitizer)
			{
				switch (usage) 
				{
					case GluonInput::TouchpadDevice:
						break;
					case GluonInput::TabletDevice:
						inputDevice = new Tablet(new InputThread(device));
						detect->addTablet(inputDevice);
						break;
					default:
						inputDevice = new InputDevice(new InputThread(device));
						detect->addUnknown(inputDevice);
						break;
				}
			}

		}
	}

	CFMutableDictionaryRef DetectMac::createMatchingDictionary(UInt32 pUsagePage, UInt32 pUsage)
	{
		CFMutableDictionaryRef matchDict = CFDictionaryCreateMutable(kCFAllocatorDefault, 1, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
		CFNumberRef usagePage = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &pUsagePage );
		CFNumberRef usage = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &pUsage);
		if(matchDict && usagePage && usage)
		{
			CFDictionarySetValue( matchDict, CFSTR( kIOHIDDeviceUsagePageKey ), usagePage);
			CFDictionarySetValue( matchDict, CFSTR( kIOHIDDeviceUsageKey ), usage);
			CFRelease(usagePage);
			CFRelease(usage);
			return matchDict;
		}
		else 
		{
			return NULL;
		}

		
	}
}
#include "detectmac.moc"
