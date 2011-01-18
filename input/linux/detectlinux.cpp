/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
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

#include "detectlinux.h"

#include "inputthread.h"
#include "detectlinuxprivate.h"

#include <core/debughelper.h>

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

// #include <libudev.h>

using namespace GluonInput;

DetectLinux::DetectLinux( QObject* parent )
    : Detect( parent )
    , d( new DetectLinuxPrivate )
{
}

DetectLinux::~DetectLinux()
{
    //    kDebug()<<"clear device...";
    //    foreach ( KCLInput * input, m_inputList)
    //    {
    //        delete input;
    //    }
}

void DetectLinux::detectDevices()
{
    DetectLinux* detect = this;
    detect->clear();
    QDir event( "/dev/input/by-path/" );
    QStringList readableInputFiles;
    QStringList unreadableInputFiles;
    QString file;
    QFileInfoList inputFileInfoList;
    QList<struct input_id> processedInputs;
    // bool processed;

    // struct udev *udev;
    // struct udev_enumerate *enumerate;
    // struct udev_list_entry *devices;
    // struct udev_list_entry *dev_list_entry;
    // struct udev_device *dev;
    // struct udev_device *parent_dev;
    // struct input_id currentInputDeviceInfo;

    inputFileInfoList = event.entryInfoList( QDir::Files );
    foreach( QFileInfo inputFileInfo, inputFileInfoList )
    {
        file = inputFileInfo.filePath();
        if( access( file.toUtf8(), R_OK ) != -1 )
            readableInputFiles.append( file );
        else
            unreadableInputFiles.append( file );
    }

    if( !unreadableInputFiles.isEmpty() )
    {
    }
    else
    {
        // Low-level stance
        foreach( const QString & name, readableInputFiles )
        {
            InputDevice* device = 0;
            InputThread* thread = new InputThread( name );
            if( !thread->error() )
            {
                switch( thread->deviceType() )
                {
                case GluonInput::KeyboardDevice:
                    device = new Keyboard( thread );
                    detect->addKeyboard( static_cast<Keyboard*>( device ) );
                    break;

                case GluonInput::MouseDevice:
                    device = new Mouse( thread );
                    detect->addMouse( static_cast<Mouse*>( device ) );
                    break;

                case GluonInput::TouchpadDevice:
                    device = new Mouse( thread );
                    detect->addMouse( static_cast<Mouse*>( device ) );
                    break;

                case GluonInput::JoystickDevice:
                    device = new Joystick( thread );
                    detect->addJoystick( static_cast<Joystick*>( device ) );
                    break;

                case GluonInput::TouchDevice:
                    device = new Touch( thread );
                    detect->addTouch( static_cast<Touch*>( device ) );
                    break;

                case GluonInput::UnknownDevice:
                    device = new InputDevice( thread );
                    detect->addUnknown( device );
                    break;
                }

                processedInputs.append( thread->device_info() );
                detect->addInput( device );
            }
        }
    }
    // #ifdef 0
    // [> Create the udev object <]
    // udev = udev_new();
    // if (!udev)
    // qWarning() << "Cannot create udev" << endl;

    // [> Create a list of the devices in the 'hidraw' subsystem. <]
    // enumerate = udev_enumerate_new(udev);
    // udev_enumerate_add_match_subsystem(enumerate, "input");
    // udev_enumerate_scan_devices(enumerate);
    // devices = udev_enumerate_get_list_entry(enumerate);
    /* For each item enumerated, print out its information.
     * udev_list_entry_foreach is a macro which expands to
     * a loop. The loop will be executed for each member in
     * devices, setting dev_list_entry to a list entry
     * which contains the device's path in /sys.
     */
    // udev_list_entry_foreach(dev_list_entry, devices) {
    // const char *path;

    // [> Get the filename of the /sys entry for the device
    // and create a udev_device object (dev) representing it */
    // path = udev_list_entry_get_name(dev_list_entry);
    // dev = udev_device_new_from_syspath(udev, path);

    // parent_dev = udev_device_get_parent_with_subsystem_devtype(dev, "input", 0);
    // if (parent_dev) {
    // udev_device_unref(parent_dev);
    // continue;
    // }

    // if (udev_device_get_sysattr_value(dev, "id/bustype"))
    // currentInputDeviceInfo.bustype = atoi(udev_device_get_sysattr_value(dev, "id/bustype"));
    // if (udev_device_get_sysattr_value(dev, "id/vendor"))
    // currentInputDeviceInfo.vendor = atoi(udev_device_get_sysattr_value(dev,"id/vendor"));
    // if (udev_device_get_sysattr_value(dev, "id/product"))
    // currentInputDeviceInfo.product = atoi(udev_device_get_sysattr_value(dev, "id/product"));
    // if (udev_device_get_sysattr_value(dev, "id/version"))
    // currentInputDeviceInfo.version = atoi(udev_device_get_sysattr_value(dev, "id/version"));

    /* The input device has been already processed, has read access
     * credential
     */
    // processed = false;
    // foreach(struct input_id inputID, processedInputs) {
    // if (inputID.bustype == currentInputDeviceInfo.bustype
    // && inputID.vendor == currentInputDeviceInfo.vendor
    // && inputID.product == currentInputDeviceInfo.product
    // && inputID.version == currentInputDeviceInfo.version) {
    // processed = true;
    // break;
    // }
    // }

    // if (processed)
    // continue;

    // InputDevice *device = 0;
    // InputThread *thread = new InputThread(dev);
    // if (!thread->error()) {
    // switch (thread->deviceType()) {
    // case GluonInput::KeyboardDevice:
    // device = new Keyboard(thread);
    // detect->addKeyboard(static_cast<Keyboard *>(device));
    // break;

    // case GluonInput::MouseDevice:
    // device = new Mouse(thread);
    // detect->addMouse(static_cast<Mouse *>(device));
    // break;

    // case GluonInput::TouchpadDevice:
    // device = new Mouse(thread);
    // detect->addMouse(static_cast<Mouse *>(device));
    // break;

    // case GluonInput::JoystickDevice:
    // device = new Joystick(thread);
    // detect->addJoystick(static_cast<Joystick *>(device));
    // break;

    // case GluonInput::TouchDevice:
    // device = new Touch(thread);
    // detect->addTouch(static_cast<Touch *>(device));
    // break;

    // case GluonInput::UnknownDevice:
    // device = new InputDevice(thread);
    // detect->addUnknown(device);
    // break;
    // }

    // detect->addInput(device);
    // }
    // }

    // [> Free the enumerator object <]
    // udev_enumerate_unref(enumerate);

    // udev_unref(udev);
    // #endif
}

void DetectLinux::setAllEnabled( bool enable )
{
    foreach( InputDevice * input, inputList() )
    {
        input->setEnabled( enable );
    }
}

void DetectLinux::clear()
{
    d->inputList.clear();
    d->keyboardList.clear();
    d->mouseList.clear();
    d->joystickList.clear();
    d->touchList.clear();
    d->unknownList.clear();
}

void DetectLinux::addInput( InputDevice* i )
{
    d->inputList.append( i );
}

void DetectLinux::addKeyboard( Keyboard* keyboard )
{
    d->keyboardList.append( keyboard );
}

void DetectLinux::addMouse( Mouse* mouse )
{
    d->mouseList.append( mouse );
}

void DetectLinux::addJoystick( Joystick* joystick )
{
    d->joystickList.append( joystick );
}

void DetectLinux::addTouch( Touch* touch )
{
    d->touchList.append( touch );
}

void DetectLinux::addUnknown( InputDevice* i )
{
    d->unknownList.append( i );
}

QList<InputDevice*> DetectLinux::inputList()
{
    return d->inputList;
}

QList<Keyboard*> DetectLinux::keyboardList()
{
    return d->keyboardList;
}

QList<Mouse*> DetectLinux::mouseList()
{
    return d->mouseList;
}

QList<Joystick*> DetectLinux::joystickList()
{
    return d->joystickList;
}

QList<Touch*> DetectLinux::touchList()
{
    return d->touchList;
}

QList<InputDevice*> DetectLinux::unknownDeviceList()
{
    return d->unknownList;
}

#include "detectlinux.moc"
