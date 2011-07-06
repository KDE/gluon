/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "detectmac.h"

#include "gluon_input_export.h"
#include "gluondevices.h"
#include "inputthread.h"

#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDUsageTables.h>

using namespace GluonInput;

class DetectMac::Private
{
    public:
        Private()
        {
            deviceManager = 0;
            devices = 0;
        }

        Private( Private& other )
            : m_inputList( other.m_inputList )
            , m_keyboardList( other.m_keyboardList )
            , m_mouseList( other.m_mouseList )
            , m_joystickList( other.m_joystickList )
            , m_touchList( other.m_touchList )
            , m_unknownList( other.m_unknownList )
            , deviceManager( other.deviceManager )
            , devices( other.devices )
        {
        }

        ~Private() {}

        QList<InputDevice*> m_inputList;
        QList<Keyboard*> m_keyboardList;
        QList<Mouse*> m_mouseList;
        QList<Joystick*> m_joystickList;
        QList<Touch*> m_touchList;
        QList<InputDevice*> m_unknownList;
        IOHIDManagerRef deviceManager;
        CFSetRef devices;
};


DetectMac::DetectMac( QObject* parent )
    : Detect( parent )
    , d( new Private() )
{
}

DetectMac::~DetectMac()
{
    CFRelease( d->deviceManager );
    //CFRelease(d->devices);
}

bool DetectMac::isReadable()
{
    return false;
}

void DetectMac::detectDevices()
{
    if( d->deviceManager == 0 )
    {
        d->deviceManager = IOHIDManagerCreate( kCFAllocatorDefault, kIOHIDOptionsTypeNone );
    }

    CFMutableDictionaryRef dict;
    CFMutableArrayRef matchingArray = CFArrayCreateMutable( kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks );
    //keyboard
    dict = createMatchingDictionary( kHIDPage_GenericDesktop, kHIDUsage_GD_Keyboard );
    if( dict )
    {
        CFArrayAppendValue( matchingArray, dict );
        CFRelease( dict );
    }

    //mouse
    dict = createMatchingDictionary( kHIDPage_GenericDesktop, kHIDUsage_GD_Mouse );
    if( dict )
    {
        CFArrayAppendValue( matchingArray, dict );
        CFRelease( dict );
    }

    //joystick
    dict = createMatchingDictionary( kHIDPage_GenericDesktop, kHIDUsage_GD_Joystick );
    if( dict )
    {
        CFArrayAppendValue( matchingArray, dict );
        CFRelease( dict );
    }

    //digitizer / touch
    dict = createMatchingDictionary( kHIDPage_Digitizer, kHIDUsage_Dig_Digitizer );
    if( dict )
    {
        CFArrayAppendValue( matchingArray, dict );
        CFRelease( dict );
    }

    //touchpad
    dict = createMatchingDictionary( kHIDPage_Digitizer, kHIDUsage_Dig_TouchPad );
    if( dict )
    {
        CFArrayAppendValue( matchingArray, dict );
        CFRelease( dict );
    }

    if( CFGetTypeID( d->deviceManager ) == IOHIDManagerGetTypeID() )
    {
        IOHIDManagerSetDeviceMatchingMultiple( d->deviceManager, matchingArray );

        if( IOHIDManagerOpen( d->deviceManager, kIOHIDOptionsTypeNone ) == kIOReturnSuccess )
        {
            d->devices = IOHIDManagerCopyDevices( d->deviceManager );

            if( CFSetGetCount( d->devices ) > 0 )
            {
                CFSetApplyFunction( d->devices, createDevices, this );
            }
        }
    }
}

QList<InputDevice*> DetectMac::inputList()
{
    return d->m_inputList;
}

QList<Keyboard*> DetectMac::keyboardList()
{
    return d->m_keyboardList;
}

QList<Mouse*> DetectMac::mouseList()
{
    return d->m_mouseList;
}

QList<Joystick*> DetectMac::joystickList()
{
    return d->m_joystickList;
}

QList<Touch*> DetectMac::touchList()
{
    return d->m_touchList;
}

QList<InputDevice*> DetectMac::unknownDeviceList()
{
    return d->m_unknownList;
}


void DetectMac::addInput( InputDevice* i )
{
    d->m_inputList.append( i );
}

void DetectMac::addKeyboard( Keyboard* keybd )
{
    d->m_keyboardList.append( keybd );
    d->m_inputList.append( keybd );
}

void DetectMac::addMouse( Mouse* mouse )
{
    d->m_mouseList.append( mouse );
    d->m_inputList.append( mouse );
}

void DetectMac::addJoystick( Joystick* joystick )
{
    d->m_joystickList.append( joystick );
    d->m_inputList.append( joystick );
}

void DetectMac::addTouch( Touch* touch )
{
    d->m_touchList.append( touch );
    d->m_inputList.append( touch );
}

void DetectMac::addUnknown( InputDevice* i )
{
    d->m_unknownList.append( i );
    d->m_inputList.append( i );
}

void DetectMac::clear()
{
    d->m_inputList.clear();
    d->m_keyboardList.clear();
    d->m_mouseList.clear();
    d->m_joystickList.clear();
    d->m_touchList.clear();
    d->m_unknownList.clear();
}

void DetectMac::setAllEnabled( bool enable )
{
    foreach( InputDevice * input, inputList() )
    {
        input->setEnabled( enable );
    }
}

void DetectMac::createDevices( const void* value, void* context )
{
    IOHIDDeviceRef device = ( IOHIDDeviceRef )value;
    DetectMac* detect = ( DetectMac* ) context;

    if( CFGetTypeID( device ) == IOHIDDeviceGetTypeID() )
    {
        IOHIDDeviceOpen( device, kIOHIDOptionsTypeNone );

        int usagePage = NULL;
        int usage = NULL;

        CFTypeRef type = IOHIDDeviceGetProperty( device, CFSTR( kIOHIDDeviceUsagePageKey ) );

        if( type )
        {
            // if this is a number
            if( CFNumberGetTypeID() == CFGetTypeID( type ) )
            {
                // get it's value
                CFNumberGetValue( ( CFNumberRef )type, kCFNumberSInt32Type, &usagePage );
            }
            CFRelease( type );
        }

        type = IOHIDDeviceGetProperty( device, CFSTR( kIOHIDDeviceUsageKey ) );

        if( type )
        {
            // if this is a number
            if( CFNumberGetTypeID() == CFGetTypeID( type ) )
            {
                // get it's value
                CFNumberGetValue( ( CFNumberRef )type, kCFNumberSInt32Type, &usage );
            }
            CFRelease( type );
        }

        if( !usage || !usagePage )
        {
            type = IOHIDDeviceGetProperty( device, CFSTR( kIOHIDPrimaryUsagePageKey ) );

            if( type )
            {
                // if this is a number
                if( CFNumberGetTypeID() == CFGetTypeID( type ) )
                {
                    // get it's value
                    CFNumberGetValue( ( CFNumberRef )type, kCFNumberSInt32Type, &usagePage );
                }
                CFRelease( type );
            }

            type = IOHIDDeviceGetProperty( device, CFSTR( kIOHIDPrimaryUsageKey ) );

            if( type )
            {
                // if this is a number
                if( CFNumberGetTypeID() == CFGetTypeID( type ) )
                {
                    // get it's value
                    CFNumberGetValue( ( CFNumberRef )type, kCFNumberSInt32Type, &usage );
                }
                CFRelease( type );
            }

        }

        if( !usage || !usagePage )
        {
            usagePage = 0;
        }

        InputDevice* inputDevice = 0;
        if( usagePage == kHIDPage_GenericDesktop )
        {
            switch( usage )
            {
                case GluonInput::KeyboardDevice:
                    inputDevice = new Keyboard( new InputThread( device ) );
                    detect->addKeyboard( static_cast<Keyboard*>( inputDevice ) );
                    break;
                case GluonInput::MouseDevice:
                    inputDevice = new Mouse( new InputThread( device ) );
                    detect->addMouse( static_cast<Mouse*>( inputDevice ) );
                    break;
                case GluonInput::JoystickDevice:
                    inputDevice = new Joystick( new InputThread( device ) );
                    detect->addJoystick( static_cast<Joystick*>( inputDevice ) );
                    break;
                default:
                    inputDevice = new InputDevice( new InputThread( device ) );
                    detect->addUnknown( inputDevice );
                    break;
            }
        }
        else if( usagePage == kHIDPage_Digitizer )
        {
            switch( usage )
            {
                    /*case GluonInput::TouchpadDevice:
                      break;*/
                case GluonInput::TouchDevice:
                    inputDevice = new Touch( new InputThread( device ) );
                    detect->addTouch( static_cast<Touch*>( inputDevice ) );
                    break;
                default:
                    inputDevice = new InputDevice( new InputThread( device ) );
                    detect->addUnknown( inputDevice );
                    break;
            }
        }

    }
}

CFMutableDictionaryRef DetectMac::createMatchingDictionary( UInt32 pUsagePage, UInt32 pUsage )
{
    CFMutableDictionaryRef matchDict = CFDictionaryCreateMutable( kCFAllocatorDefault, 1, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks );
    CFNumberRef usagePage = CFNumberCreate( kCFAllocatorDefault, kCFNumberIntType, &pUsagePage );
    CFNumberRef usage = CFNumberCreate( kCFAllocatorDefault, kCFNumberIntType, &pUsage );
    if( matchDict && usagePage && usage )
    {
        CFDictionarySetValue( matchDict, CFSTR( kIOHIDDeviceUsagePageKey ), usagePage );
        CFDictionarySetValue( matchDict, CFSTR( kIOHIDDeviceUsageKey ), usage );
        CFRelease( usagePage );
        CFRelease( usage );
        return matchDict;
    }
    else
    {
        return 0;
    }
}

#include "detectmac.moc"
