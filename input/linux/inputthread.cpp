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

InputThread::InputThread(const QString &devicePath, QObject *parent)
		: QThread(parent)
        , d(new InputThreadPrivate)
{
	d->m_devicePath = devicePath;
    openDevice(devicePath);
}

InputThread::~InputThread()
{
	close(d->m_fd);
}

void InputThread::run()
{
	while (1)
	{
		struct input_event ev;
		int rd = read(d->m_fd, &ev, sizeof(struct input_event));
		if (rd >= (int) sizeof(struct input_event))
		{
			QEvent::Type eventType = QEvent::Type(QEvent::User + ev.type);

			switch(eventType)
			{
				case GluonInput::Button:
					emit this->buttonStateChanged(ev.code, ev.value);
					break;
				case GluonInput::RelativeAxis:
					emit this->relAxisMoved(ev.code, ev.value);
					break;
				case GluonInput::AbsoluteAxis:
					emit this->absAxisMoved(ev.code, ev.value);
					break;
			}
		}
	}
}

bool InputThread::openDevice(const QString &devicePath)
{
    if ((d->m_fd = open(devicePath.toUtf8(), O_RDONLY)) == -1) {
        qDebug() << "Could not open device: " << devicePath;
        d->m_error = true;
        d->m_msgError += "Could not open the device\n";
		return false;
	}

	readInformation();
	return true;
}

void InputThread::readInformation()
{
	/*if (!QFile::exists(d->m_devicePath))
	{
		qDebug() << "m_devicePath does not exist";
		d->m_error = true;
		d->m_msgError += "device url does not exist \n";
		return;
	}*/

    if (d->m_fd == -1) {
        qDebug() << "Device is not open";
		d->m_error = true;
        d->m_msgError = "Device is not open\n";
		return;
	}

    if ((d->m_fd = open(d->m_devicePath.toUtf8(), O_RDONLY)) == -1) {
		qDebug() << "Could not open device" << d->m_devicePath;
		d->m_error = true;
        d->m_msgError = "Could not open the device \n";
		return;
	}

    // Get the device ID
    if (ioctl(d->m_fd, EVIOCGID, &d->m_device_info)) {
		qDebug() << "Could not retrieve information of device" << d->m_devicePath;
        d->m_msgError = "Could not retrieve information of device\n";
		d->m_error = true;
		return;
	}

	char name[256] = "Unknown";
    // Get the device name
    if (ioctl(d->m_fd, EVIOCGNAME(sizeof(name)), name) == -1) {
        qDebug() << "Could not retrieve name of device" << d->m_devicePath;
        d->m_msgError = "Could not retrieve name of device\n";
		d->m_error = true;
		return;
	}
	d->m_deviceName = QString(name);

	///this next bit can be shared across platform
	unsigned long bit[EV_MAX][NBITS(KEY_MAX)];
	int abs[5];
	memset(bit, 0, sizeof(bit));
    // Get event bits
	ioctl(d->m_fd, EVIOCGBIT(0, EV_MAX), bit[0]);

	d->m_buttonCapabilities.clear();
	d->m_absAxisInfos.clear();

    for (int i = 0; i < EV_MAX; ++i) 	{
        if (test_bit(i, bit[0])) {
            if (!i) {
				continue;
			}

            // Get event bits
			ioctl(d->m_fd, EVIOCGBIT(i, KEY_MAX), bit[i]);
            for (int j = 0; j < KEY_MAX; ++j) {
                if (test_bit(j, bit[i])) {
                    if (i == EV_KEY) {
						d->m_buttonCapabilities.append(j);
					}

                    if (i == EV_REL) {
						d->m_relAxisCapabilities.append(j);
					}

                    if (i == EV_ABS) {
                        // Get abs value/limits
						ioctl(d->m_fd, EVIOCGABS(j), abs);
                        AbsVal cabs(0, 0, 0, 0);
                        for (int k = 0; k < 5; ++k) {
                            if ((k < 3) || abs[k]) {
                                switch (k) {
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
						d->m_absAxisCapabilities.append(j);
						d->m_absAxisInfos[j] = cabs;
					}
				}
			}
		}
	}

	//===============Find Force feedback ?? ===============

	d->m_deviceType = GluonInput::UnknownDevice;

    if (d->m_buttonCapabilities.contains(BTN_STYLUS)) {
		d->m_deviceType  = GluonInput::TabletDevice;
	}

	if (d->m_buttonCapabilities.contains(BTN_STYLUS)
            || d->m_buttonCapabilities.contains(ABS_PRESSURE)) {
		d->m_deviceType  = GluonInput::MouseDevice;
	}

    if (d->m_buttonCapabilities.contains(BTN_TRIGGER)) {
		d->m_deviceType  = GluonInput::JoystickDevice;
	}

    if (d->m_buttonCapabilities.contains(BTN_MOUSE)) {
		d->m_deviceType  = GluonInput::MouseDevice;
	}

	if (d->m_buttonCapabilities.contains(KEY_ESC))	{
		d->m_deviceType  = GluonInput::KeyboardDevice;
	}
}

int InputThread::getJoystickXAxis()
{
	return ABS_X;
}

int InputThread::getJoystickYAxis()
{
	return ABS_Y;
}

int InputThread::getJoystickZAxis()
{
	return ABS_Z;
}

void InputThread::stop()
{
    quit();
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
	close(d->m_fd);
}

#include "inputthread.moc"
