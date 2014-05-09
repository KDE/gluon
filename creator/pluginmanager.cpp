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
#include <KDE/KMessageBox>

using namespace GluonCreator;

GLUON_DEFINE_SINGLETON( PluginManager )

class PluginManager::PluginManagerPrivate
{
    public:
        PluginManagerPrivate() : mainWindow( 0 ) {}
        virtual ~PluginManagerPrivate() {}

        QHash<QString, Plugin*> loadedPlugins;
        KXmlGuiWindow* mainWindow;

	static const QStringList requiredPlugins;
};

const QStringList PluginManager::PluginManagerPrivate::requiredPlugins = QStringList() << 
    "gluoncreator_dockplugin_projectdock" <<
    "gluoncreator_dockplugin_scenedock" <<
    "gluoncreator_dockplugin_propertiesdock" <<
    "gluoncreator_dockplugin_componentsdock" <<
    "gluoncreator_dockplugin_messagedock";

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
    int requiredPluginCount = 0;
    KConfigGroup group = KGlobal::config()->group( "Plugins" );
    KService::List offers = KServiceTypeTrader::self()->query(
                                QString::fromLatin1( "GluonCreator/Plugin" ),
                                QString( "[X-KDE-GluonCreatorPluginVersion] == %1" ).arg( GLUONCREATOR_PLUGIN_VERSION ) );

    KService::List::const_iterator iter;
    for( iter = offers.begin(); iter < offers.end(); ++iter )
    {
        QString error;
        KService::Ptr service = *iter;

        QString serviceName = service->desktopEntryName();
        bool loadPlugin = group.readEntry<bool>( QString( "%1Enabled" ).arg( serviceName ), true );

        if( d->requiredPlugins.contains( serviceName ) )
	{
	    DEBUG_TEXT2( "%1 is a required plugin", serviceName );
            requiredPluginCount++;
	}

        if( !d->loadedPlugins.contains( serviceName ) && loadPlugin )
        {
            KPluginLoader loader( service->library() );
            KPluginFactory* factory = loader.factory();

            if( !factory )
            {
                DEBUG_TEXT2( "KPluginFactory could not load the plugin: %1", service->library() )
                DEBUG_TEXT( loader.errorString() );
                continue;
            }

            Plugin* plugin = factory->create<Plugin>( this );

            if( plugin )
            {
                DEBUG_TEXT2( "Load plugin: %1", service->name() )
                plugin->load( d->mainWindow );
                d->loadedPlugins.insert( serviceName, plugin );
            }
            else
            {
                DEBUG_TEXT( error )
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

    if( requiredPluginCount < d->requiredPlugins.count() )
    {
        KMessageBox::error( d->mainWindow, i18n( "Could not load all required plugins!" ), i18n( "Unable to load plugins" ) ); 
	qFatal( "Unable to load all required plugins!" );
    }
}

PluginManager::PluginManager( QObject* parent )
    : GluonCore::Singleton< GluonCreator::PluginManager >( parent ), d( new PluginManagerPrivate )
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
