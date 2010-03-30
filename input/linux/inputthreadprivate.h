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
#ifndef INPUTTHREADPRIVATE_H
#define INPUTTHREADPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>

#include "gluonbuttons.h"
#include "absval.h"

namespace GluonInput
{
    class InputThreadPrivate : public QSharedData
    {
        public:
            InputThreadPrivate();
            InputThreadPrivate(InputThreadPrivate &other);

            int m_fd;
            struct input_id m_device_info;
            struct input_event m_currentEvent;
            QString m_devicePath;

            int m_vendor;
            int m_product;
            int m_version;
            int m_bustype;

            QString m_deviceName;
            QString m_msgError;

            bool m_error;

            GluonInput::DeviceFlag m_deviceType;

            QList<int> m_buttonCapabilities; // list of button capability. BTN_ESC, BTN_F1 etc....
            QList<int> m_relAxisCapabilities; // list of rel Axis capability..
            QList<int> m_absAxisCapabilities; // list of abs Axis capabilty
            QMap<int, AbsVal> m_absAxisInfos; // each Absolute Axis has a sub info called AbsVal. [ABS_RX] = AbsVal.
    };
}
#endif
