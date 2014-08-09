/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2014 Arjen Hiemstra <ahiemstra@heimr.nl>
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
 *
 */

#ifndef GLUONINPUT_DEVICEPLUGIN_H
#define GLUONINPUT_DEVICEPLUGIN_H

#include <QtCore/QObject>

namespace GluonInput
{
    class InputDevice;

    class DevicePlugin : public QObject
    {
        Q_OBJECT

        public:
            explicit DevicePlugin( QObject* parent = 0 ) : QObject( parent ) { }
            virtual ~DevicePlugin() { }

            virtual InputDevice* device() = 0;
    };
}

Q_DECLARE_INTERFACE( GluonInput::DevicePlugin, "org.kde.gluon.input.device" )

#define GLUONINPUT_DEVICEPLUGIN \
    Q_INTERFACES( GluonInput::DevicePlugin )\
    Q_PLUGIN_METADATA( IID "org.kde.gluon.input.device" )

#endif // GLUONINPUT_DEVICEPLUGIN_H
