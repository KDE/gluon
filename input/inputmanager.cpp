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

#include "inputmanager.h"

#include <QtCore/QHash>
#include <QtCore/QStringList>
#include <QtCore/QCoreApplication>

#include <core/pluginloader.h>
#include <core/debughelper.h>

#include "inputdevice.h"
#include "platformplugin.h"
#include "deviceplugin.h"

using namespace GluonInput;

GLUON_DEFINE_SINGLETON( InputManager );

class InputManager::Private
{
    public:
        PlatformPlugin* platform = nullptr;

        QObject* filterObject = nullptr;

        QHash< QString, InputDevice* > devices;

        QHash< QString, DevicePlugin* > devicePlugins;
};

PlatformPlugin* InputManager::platform() const
{
    return d->platform;
}

void InputManager::addDevice( const QString& id, InputDevice* object )
{
    if( !d->devices.contains( id ) )
    {
        d->devices.insert( id, object );
        emit devicesChanged();
    }
}

InputDevice* InputManager::device( const QString& id ) const
{
    if( d->devices.contains( id ) )
        return d->devices.value( id );

    return nullptr;
}

void InputManager::removeDevice( const QString& id )
{
    if( d->devices.contains( id ) )
    {
        d->devices.remove( id );
        emit devicesChanged();
    }
}

void InputManager::removeDevice( InputDevice* object )
{
    Q_ASSERT( object );
    removeDevice( d->devices.key( object ) );
}

void InputManager::destroyDevice( const QString& id )
{
    if( d->devices.contains( id ) )
    {
        d->devices.value( id )->deleteLater();
        d->devices.remove( id );
        emit devicesChanged();
    }
}

void InputManager::destroyDevice( InputDevice* object )
{
    Q_ASSERT( object );
    destroyDevice( d->devices.key( object ) );
}

QList< InputDevice* > InputManager::allDevices() const
{
    return d->devices.values();
}

void InputManager::initialize()
{
    GluonCore::PluginLoader loader("gluoninput_platform");
    d->platform = qobject_cast< PlatformPlugin* >( loader.load( this ) );

    if( !d->platform )
        qFatal( "Abort: Could not find an input platform plugin!" );

    d->platform->initialize();

    QStringList devices = d->platform->listDevices();
    for( const QString& device : devices )
    {
        loadDevice( device );
    }
}

QObject* InputManager::filterObject() const
{
    return d->filterObject ? d->filterObject : QCoreApplication::instance();
}

void InputManager::loadDevice(const QString& device)
{
    QString pluginName = "gluoninput_" + device;

    DevicePlugin* plugin = d->devicePlugins.value( pluginName );
    if( !plugin )
    {
        GluonCore::PluginLoader loader( pluginName );
        plugin = qobject_cast< DevicePlugin* >( loader.load( this ) );

        if( plugin )
            d->devicePlugins.insert( pluginName, plugin );
    }

    if( plugin )
    {
        addDevice( device, plugin->device() );
    }
    else
    {
        DEBUG_BLOCK
        DEBUG_TEXT2( "Could not find plugin for device %1", device )
    }
}

void InputManager::setFilterObject(QObject* object)
{
    d->filterObject = object;
}

InputManager::InputManager( QObject* parent )
    : Singleton< GluonInput::InputManager >( parent )
{

}

InputManager::~InputManager()
{
}
