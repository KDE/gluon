/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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
#ifndef GLUONQTBUTTONS_H
#define GLUONQTBUTTONS_H

#include "gluon_input_export.h"
#include "gluonqtdevices.h"

#include <core/singleton.h>

namespace GluonInput
{
    class GluonQtButtons : public GluonCore::Singleton<GluonQtButtons>
    {
            Q_OBJECT
            Q_ENUMS( Qt::Key )
            Q_ENUMS( Absolute )
            Q_ENUMS( Relative )
            GLUON_SINGLETON( GluonQtButtons )

        public:
            enum Relative
            {
                X_REL,
                Y_REL,
                Z_REL,
                HWHEEL = 6,
                DIAL,
                WHEEL_REL,
                MISC_REL
            };

            enum Absolute
            {
                X_ABS,
                Y_ABS,
                Z_ABS,
                Rx,
                Ry,
                Rz,
                THROTTLE,
                RUDDER,
                WHEEL_ABS,
                GAS,
                BRAKE,
                HAT_ZERO_X = 16,
                HAT_ZERO_Y,
                HAT_ONE_X,
                HAT_ONE_Y,
                HAT_TWO_X,
                HAT_TWO_Y,
                HAT_THREE_X,
                HAT_THREE_Y,
                PRESSURE,
                DISTANCE,
                X_TILT,
                Y_TILT,
                TOOLWIDTH,
                VOLUME = 32,
                MISC_ABS = 40
            };

            QString buttonName( DeviceQtFlag deviceType, int code );
            QString axisName( DeviceQtFlag deviceType, int code );

        private:
            ~GluonQtButtons();
    };
}

#endif
