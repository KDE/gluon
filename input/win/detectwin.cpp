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
#include "kcldetectwin.h"

#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/hid/IOHIDLib.h>

KCLDetectWin::KCLDetectWin(QObject * parent)
        : QObject(parent)
{
}

KCLDetectWin::~KCLDetectWin()
{
    //    kDebug()<<"clear device...";
    //    foreach ( KCLInput * input, m_inputList)
    //    {
    //        delete input;
    //    }
}

void KCLDetectWin::searchDevice()
{
    KCLDetectWin *detect = this;

    ///move it out and maybe in detection
    /*IOHIDManagerRef miw = IOHIDManagerCreate( kCFAllocatorDefault, kIOHIDOptionsTypeNone);

     if ( CFGetTypeID( miw ) == IOHIDManagerGetTypeID( ) )
     {
     IOHIDManagerSetDeviceMatching(miw, NULL);

     IOReturn success = IOHIDManagerOpen(miw, kIOHIDOptionsTypeNone);

     if(success == kIOReturnSuccess)
     {
     CFSetRef devicesSet = IOHIDManagerCopyDevices(miw);

     if(CFSetGetCount(devicesSet) > 0)
     {
     CFSetApplyFunction(devicesSet, callBack, NULL);
     }
     // CFRelease(devicesSet);
     }
     }*/

    detect->setAllEnable();
}

void KCLDetectWin::clear()
{
    m_inputList.clear();
    m_keyboardList.clear();
    m_mouseList.clear();
    m_joystickList.clear();
    m_tabletList.clear();
    m_unknownList.clear();
}
