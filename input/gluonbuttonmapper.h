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
#ifndef GLUONBUTTONMAPPER_H
#define GLUONBUTTONMAPPER_H

#include <QtCore/QObject>
#include <QtCore/QSharedData>

#include "gluon_input_export.h"
#include "gluondevices.h"
#include "gluon_input_export.h"
#include "core/singleton.h"
#include "gluonmacbuttons.h"

namespace GluonInput
{
    class InputDevice;
    class InputEvent;
    class GluonButtonMapperPrivate;

    class GLUON_INPUT_EXPORT GluonButtonMapper :public GluonCore::Singleton<GluonButtonMapper>
    {
            Q_OBJECT		
        public:
            GluonButtonMapper();

            void setButtonMapping(const KeyboardButton button, const QString &name);
            void removeButtonMapping(const KeyboardButton button, const QString &name);
            void setAbsAxisMapping(const QString &name, InputDevice * input, int axis);
            void setRelAxisMapping(const QString &name, InputDevice* input, int axis);
            void removeAbsAxisMapping(const KeyboardButton,const QString name);
            void removeRelAxisMapping(const ,const QString name);
			
			QString buttonName(DeviceFlag deviceType , int code);
			QString axisName(DeviceFlag deviceType, int code);
        private:
            ~GluonButtonMapper();
            QSharedDataPointer<GluonButtonMapperPrivate> d;
    };
}

#endif // KCLCUSTOMINPUT_H
