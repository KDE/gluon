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

#ifndef GLUONINPUT_INPUTMANAGER_H
#define GLUONINPUT_INPUTMANAGER_H

#include <core/manager.h>
#include <core/singleton.h>
#include <core/privatepointer.h>

#include "gluoninput_export.h"

namespace GluonInput
{
    class InputDevice;
    class PlatformPlugin;

    class GLUONINPUT_EXPORT InputManager : public GluonCore::Singleton< InputManager >
    {
        Q_OBJECT
        GLUON_SINGLETON( InputManager )

        public:
            PlatformPlugin* platform() const;

            virtual void addDevice( const QString& id, InputDevice* object );
            virtual InputDevice* device( const QString& id ) const;
            virtual void removeDevice( const QString& id );
            virtual void removeDevice( InputDevice* object );
            virtual void destroyDevice( const QString& id );
            virtual void destroyDevice( InputDevice* object );
            virtual QList< InputDevice* > allDevices() const;

            void initialize();

            QObject* filterObject() const;

        public Q_SLOTS:
            void loadDevice( const QString& device );
            void setFilterObject( QObject* object );

        Q_SIGNALS:
            void devicesChanged();

        private:
            ~InputManager();
            GLUON_PRIVATE_POINTER;
    };
}

#endif // GLUONINPUT_INPUTMANAGER_H
