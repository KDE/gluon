/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "pluginmanager.h"
#include "plugin.h"

#include <core/debughelper.h>

#include <KDE/KServiceTypeTrader>
#include <KDE/KXmlGuiWindow>

using namespace GluonCreator;

template<> GLUON_CREATOR_VISIBILITY PluginManager* GluonCore::Singleton<PluginManager>::m_instance = 0;

class PluginManager::PluginManagerPrivate
{
    public:
        PluginManagerPrivate() : mainWindow(0) {}
        virtual ~PluginManagerPrivate() {}

        QHash<QString, Plugin*> loadedPlugins;
        KXmlGuiWindow* mainWindow;
};

QList< KPluginInfo > PluginManager::pluginInfos() const
{
    return KPluginInfo::fromServices( KServiceTypeTrader::self()->query( "GluonCreator/Plugin" ) );
}

void PluginManager::setMainWindow( KXmlGuiWindow* window )
{
    d->mainWindow = window;
}

void PluginManager::loadPlugins()
{
    DEBUG_FUNC_NAME
    KConfigGroup group = KGlobal::config()->group( "Plugins" );
    KService::List offers = KServiceTypeTrader::self()->query(
            QString::fromLatin1("GluonCreator/Plugin" ),
            QString( "[X-KDE-GluonCreatorPluginVersion] == %1" ).arg( GLUONCREATOR_PLUGIN_VERSION ) );

    KService::List::const_iterator iter;
    for( iter = offers.begin(); iter < offers.end(); ++iter )
    {
        QString error;
        KService::Ptr service = *iter;

        QString serviceName = service->desktopEntryName();
        bool loadPlugin = group.readEntry<bool>( QString( "%1Enabled" ).arg( serviceName ), true );

        if( !d->loadedPlugins.contains( serviceName ) && loadPlugin )
        {
            KPluginFactory* factory = KPluginLoader( service->library() ).factory();

            if( !factory )
            {
                DEBUG_TEXT( QString( "KPluginFactory could not load the plugin: %1" ).arg( service->library() ) );
                continue;
            }

            Plugin* plugin = factory->create<Plugin>( this );

            if( plugin )
            {
                DEBUG_TEXT( QString( "Load plugin: %1" ).arg( service->name() ) );
                plugin->load( d->mainWindow );
                d->loadedPlugins.insert( serviceName, plugin );
            }
            else
            {
                DEBUG_TEXT( error );
            }
        }
        else if( !loadPlugin && d->loadedPlugins.contains( serviceName ) )
        {
            Plugin* plugin = d->loadedPlugins.value( serviceName );
            plugin->unload( d->mainWindow );
            delete plugin;
            d->loadedPlugins.remove( serviceName );
        }
    }
}

PluginManager::PluginManager() : d( new PluginManagerPrivate )
{
}

PluginManager::~PluginManager()
{
    delete d;
}
QHash<QString, Plugin*> PluginManager::loadedPlugins()
{
    return d->loadedPlugins;
}
