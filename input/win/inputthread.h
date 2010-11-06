/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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
#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H

#include "gluon_input_export.h"
#include "gluonbuttons.h"
#include "absval.h"

#include <QtCore/QThread>

namespace GluonInput
{
    class GLUON_INPUT_EXPORT InputThread : public QThread
    {
        public:
            explicit InputThread( const QString& devicePath, QObject* parent = 0 );
            ~InputThread();
            void run();

            int joystickXAxis();
            int joystickYAxis();
            int joystickZAxis();
            void stop();

            int vendor() const;
            int product() const;
            int version() const;
            int bustype() const;

            QList<int> buttonCapabilities() const;
            QList<int> absAxisCapabilities() const;
            QList<int> relAxisCapabilities() const;
            AbsVal axisInfo( int axisCode ) const;

            const QString deviceName() const;
            GluonInput::DeviceFlag deviceType() const;

            bool isEnabled() const;

            bool error();
            QString msgError();

            QObject* parent();

        private:
            class InputThreadPrivate;
            InputThreadPrivate* const d;
    };
}

#endif //INPUTTHREAD_H
