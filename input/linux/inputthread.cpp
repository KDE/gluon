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

#include "inputthread.h"
#include "absval.h"
#include "inputthreadprivate.h"

#include <core/debughelper.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QEvent>
#include <QtCore/QStringList>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/input.h>

#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
#define OFF(x)  ((x)%BITS_PER_LONG)
#define BIT(x)  (1UL<<OFF(x))
#define LONG(x) ((x)/BITS_PER_LONG)
#define test_bit(bit, array) ((array[LONG(bit)] >> OFF(bit)) & 1)

using namespace GluonInput;

InputThread::InputThread( const QString& devicePath, QObject* parent )
    : QThread( parent )
    , d( new InputThreadPrivate )
{
    d->m_devicePath = devicePath;
    if( openDevice( devicePath ) )
        readInformation();
}

// InputThread::InputThread(struct udev_device *dev, QObject *parent)
    // : QThread(parent)
    // , d(new InputThreadPrivate)
// {
    // d->m_udevDevice = dev;
    // readSystemFS();
// }

InputThread::~InputThread()
{
    closeDevice();
}

void InputThread::run()
{
    while( 1 )
    {
        struct input_event ev;
        int rd = read( d->m_fd, &ev, sizeof( struct input_event ) );
        if( rd >= ( int ) sizeof( struct input_event ) )
        {
            QEvent::Type eventType = QEvent::Type( QEvent::User + ev.type );

            switch( eventType )
            {
                case GluonInput::Button:
                    emit this->buttonStateChanged( ev.code, ev.value );
                    break;
                case GluonInput::RelativeAxis:
                    emit this->relAxisMoved( ev.code, ev.value );
                    break;
                case GluonInput::AbsoluteAxis:
                    emit this->absAxisMoved( ev.code, ev.value );
                    break;
                default:
                    break;
            }
        }
    }
}

bool InputThread::openDevice( const QString& devicePath )
{
    if(( d->m_fd = open( devicePath.toUtf8(), O_RDONLY ) ) == -1 )
    {
        qDebug() << "Could not open device: " << devicePath;
        d->m_error = true;
        d->m_msgError += "Could not open the device\n";
        return false;
    }

    return true;
}

// int InputThread::readSystemFS()
// {

    /* From here, we can call get_sysattr_value() for each file
       in the device's /sys entry. The strings passed into these
       functions (idProduct, idVendor, serial, etc.) correspond
       directly to the files in the directory which represents
       the USB device. Note that USB strings are Unicode, UCS2
       encoded, but the strings returned from
       udev_device_get_sysattr_value() are UTF-8 encoded. */
    // d->m_deviceName = QString::fromAscii(udev_device_get_sysattr_value(d->m_udevDevice, "name"));

    // quint64 bit[EV_MAX][NBITS(KEY_MAX)];
    // int abs[5];
    // memset(bit, 0, sizeof(bit));

    // bool ok;
    // int k;
    // bit[0][0] = QString::fromAscii(udev_device_get_sysattr_value(d->m_udevDevice, "capabilities/ev")).toULong(&ok, 16);

    // for (int i = 1; i < EV_MAX; ++i) {
        // if (test_bit(i, bit[0])) {
            // if (!i)
                // continue;
            // switch (i) {
            // case EV_KEY:
            // {
                // k = 0;
                // QStringList keySections = QString::fromAscii(udev_device_get_sysattr_value(d->m_udevDevice, "capabilities/key")).split(" ");
                // for (QStringList::iterator istr = keySections.end(); istr != keySections.begin(); ++k)
                    // bit[i][k] = (--istr)->toULongLong(&ok, 16);

                // for (int j = 0; j < KEY_MAX; ++j) {
                    // if (test_bit(j, bit[i]))
                        // d->m_buttonCapabilities.append(j);
                // }
            // }
            // break;
            // case EV_REL:
                // {
                    // k = 0;
                    // QStringList relSections = QString::fromAscii(udev_device_get_sysattr_value(d->m_udevDevice, "capabilities/rel")).split(" ");
                    // for (QStringList::iterator istr = relSections.end(); istr != relSections.begin(); ++k)
                        // bit[i][k] = (--istr)->toULongLong(&ok, 16);

                    // for (int j = 0; j < KEY_MAX; ++j) {
                        // if (test_bit(j, bit[i]))
                            // d->m_relAxisCapabilities.append(j);
                    // }
                // }
                // break;
            // case EV_ABS:
                // {
                    // for (int j = 0; j < ABS_MAX; ++j) {
                        // if (test_bit(j, bit[i])) {
                            // k = 0;
                            // QStringList absSections = QString::fromAscii(udev_device_get_sysattr_value(d->m_udevDevice, "capabilities/abs")).split(" ");
                            // for (QStringList::iterator istr = absSections.end(); istr != absSections.begin(); ++k)
                                // abs[k++] = (--istr)->toULongLong(&ok, 16);

                            // AbsVal cabs(0, 0, 0, 0);
                            // for (int k = 0; k < 5; ++k) {
                                // if ((k < 3) || abs[k]) {
                                    // switch (k) {
                                    // case 0:
                                        // cabs.value = abs[k];
                                        // break;
                                    // case 1:
                                        // cabs.min = abs[k];
                                        // break;
                                    // case 2:
                                        // cabs.max = abs[k];
                                        // break;
                                    // case 3:
                                        // cabs.fuzz = abs[k];
                                        // break;
                                    // case 4:
                                        // cabs.flat = abs[k];
                                        // break;
                                    // }
                                // }
                            // }
                            // d->m_absAxisCapabilities.append(j);
                            // d->m_absAxisInfos.append(cabs);
                        // }
                    // }
                // }
                // break;
            // default:
                // break;
            // }
        // }
    // }

    // //===============Find Force feedback ?? ===============

    // d->m_deviceType = GluonInput::UnknownDevice;

    // if (d->m_buttonCapabilities.contains(BTN_TOUCH)) {
        // d->m_deviceType  = GluonInput::TouchDevice;
    // }

    // if (d->m_buttonCapabilities.contains(BTN_STYLUS)
            // || d->m_buttonCapabilities.contains(ABS_PRESSURE)) {
        // d->m_deviceType  = GluonInput::MouseDevice;
    // }

    // if (d->m_buttonCapabilities.contains(BTN_TRIGGER)) {
        // d->m_deviceType  = GluonInput::JoystickDevice;
    // }

    // if (d->m_buttonCapabilities.contains(BTN_MOUSE)) {
        // d->m_deviceType  = GluonInput::MouseDevice;
    // }

    // if (d->m_buttonCapabilities.contains(KEY_ENTER))    {
        // d->m_deviceType  = GluonInput::KeyboardDevice;
    // }

    // return 0;
// }

void InputThread::readInformation()
{
    if( d->m_fd == -1 )
    {
        qDebug() << "Device is not open";
        d->m_error = true;
        d->m_msgError = "Device is not open\n";
        return;
    }

    // Get the device ID
    if( ioctl( d->m_fd, EVIOCGID, &d->m_device_info ) )
    {
        qDebug() << "Could not retrieve information of device" << d->m_devicePath;
        d->m_msgError = "Could not retrieve information of device\n";
        d->m_error = true;
        return;
    }

    char devname[256] = "Unknown";
    // Get the device name
    if( ioctl( d->m_fd, EVIOCGNAME( sizeof( devname ) ), devname ) == -1 )
    {
        qDebug() << "Could not retrieve name of device" << d->m_devicePath;
        d->m_msgError = "Could not retrieve name of device\n";
        d->m_error = true;
        return;
    }
    d->m_deviceName = QString( devname );

    ///this next bit can be shared across platform
    unsigned long bit[EV_MAX][NBITS( KEY_MAX )];
    int abs[5];
    memset( bit, 0, sizeof( bit ) );
    // Get the feature types here
    ioctl( d->m_fd, EVIOCGBIT( 0, EV_MAX ), bit[0] );

    d->m_buttonCapabilities.clear();
    d->m_absAxisInfos.clear();

    for( int i = 0; i < EV_MAX; ++i )
    {
        if( test_bit( i, bit[0] ) )
        {
            if( !i )
            {
                continue;
            }

            // Get the features of the desired feature type here
            ioctl( d->m_fd, EVIOCGBIT( i, KEY_MAX ), bit[i] );
            switch( i )
            {
                case EV_KEY:
                {
                    for( int j = 0; j < KEY_MAX; ++j )
                    {
                        if( test_bit( j, bit[i] ) )
                            d->m_buttonCapabilities.append( j );
                    }
                }
                break;
                case EV_REL:
                {
                    for( int j = 0; j < KEY_MAX; ++j )
                    {
                        if( test_bit( j, bit[i] ) )
                            d->m_relAxisCapabilities.append( j );
                    }
                }
                break;
                case EV_ABS:
                {
                    for( int j = 0; j < ABS_MAX; ++j )
                    {
                        if( test_bit( j, bit[i] ) )
                        {
                            // Get abs value/limits
                            ioctl( d->m_fd, EVIOCGABS( j ), abs );
                            AbsVal cabs( 0, 0, 0, 0 );
                            for( int k = 0; k < 5; ++k )
                            {
                                if(( k < 3 ) || abs[k] )
                                {
                                    switch( k )
                                    {
                                        case 0:
                                            cabs.value = abs[k];
                                            break;
                                        case 1:
                                            cabs.min = abs[k];
                                            break;
                                        case 2:
                                            cabs.max = abs[k];
                                            break;
                                        case 3:
                                            cabs.fuzz = abs[k];
                                            break;
                                        case 4:
                                            cabs.flat = abs[k];
                                            break;
                                    }
                                }
                            }
                            d->m_absAxisCapabilities.append( j );
                            d->m_absAxisInfos.append( cabs );
                        }
                    }
                }
                break;
                default:
                    break;
            }
        }
    }

    //===============Find Force feedback ?? ===============

    d->m_deviceType = GluonInput::UnknownDevice;

    if( d->m_buttonCapabilities.contains( BTN_TOUCH ) )
    {
        d->m_deviceType  = GluonInput::TouchDevice;
    }

    if( d->m_buttonCapabilities.contains( BTN_STYLUS )
            || d->m_buttonCapabilities.contains( ABS_PRESSURE ) )
    {
        d->m_deviceType  = GluonInput::MouseDevice;
    }

    if( d->m_buttonCapabilities.contains( BTN_TRIGGER ) )
    {
        d->m_deviceType  = GluonInput::JoystickDevice;
    }

    if( d->m_buttonCapabilities.contains( BTN_MOUSE ) )
    {
        d->m_deviceType  = GluonInput::MouseDevice;
    }

    if( d->m_buttonCapabilities.contains( KEY_ENTER ) )
    {
        d->m_deviceType  = GluonInput::KeyboardDevice;
    }
}

int InputThread::joystickXAxis()
{
    return ABS_X;
}

int InputThread::joystickYAxis()
{
    return ABS_Y;
}

int InputThread::joystickZAxis()
{
    return ABS_Z;
}

void InputThread::stop()
{
    quit();
}

struct input_id InputThread::device_info() const
{
    return d->m_device_info;
}

int InputThread::vendor() const
{
    return d->m_device_info.vendor;
}

int InputThread::product() const
{
    return d->m_device_info.product;
}

int InputThread::version() const
{
    return d->m_device_info.version;
}

int InputThread::bustype()const
{
    return d->m_device_info.bustype;
}

QList<int> InputThread::buttonCapabilities() const
{
    return d->m_buttonCapabilities;
}

QList<int> InputThread::absAxisCapabilities() const
{
    return d->m_absAxisCapabilities;
}

QList<int> InputThread::relAxisCapabilities() const
{
    return d->m_relAxisCapabilities;
}

AbsVal InputThread::axisInfo( int axisCode ) const
{
    return d->m_absAxisInfos[axisCode];
}

const QString InputThread::deviceName() const
{
    return d->m_deviceName;
}

GluonInput::DeviceFlag InputThread::deviceType() const
{
    return d->m_deviceType;
}

bool InputThread::isEnabled() const
{
    return isRunning();
}

bool InputThread::error()
{
    return d->m_error;
}

QString InputThread::msgError()
{
    return d->m_msgError;
}

void InputThread::closeDevice()
{
    if( close( d->m_fd ) )
        qDebug() << "Could not close the device: " << d->m_devicePath << endl;
}

#include "inputthread.moc"
