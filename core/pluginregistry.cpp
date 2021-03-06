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

#include "pluginregistry.h"

#include <QtCore/QMultiHash>
#include <QtCore/QPluginLoader>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QDebug>

#include "log.h"
#include "directoryprovider.h"

using namespace GluonCore;

GLUON_DEFINE_SINGLETON( PluginRegistry )

class PluginRegistry::Private
{
    public:
        QPluginLoader* findPlugin( const QString& pluginName );
        QList< QPluginLoader* > findPluginsByType( const QString& type );

        static void updatePluginDirectories();

        PluginRegistry* q;

        QMultiHash< QString, QString > pluginNames;
        QHash< QString, QPluginLoader* > plugins;

        static const QStringList knownTypes;
        static QStringList pluginLocations;
};

const QStringList PluginRegistry::Private::knownTypes =
    QStringList() << "org.kde.gluon.core.factoryplugin"
                  << "org.kde.gluon.graphics.backend"
                  << "org.kde.gluon.input.platform"
                  << "org.kde.gluon.input.device"
                  << "org.kde.gluon.creator.dock"
                  << "org.kde.gluon.creator.tool"
                  << "org.kde.gluon.audio.decoder";

QStringList PluginRegistry::Private::pluginLocations;

QJsonObject PluginRegistry::metaData( const QString& plugin )
{
    if( d->plugins.contains( plugin ) )
        return d->plugins.value( plugin )->metaData();

    QPluginLoader* loader = d->findPlugin( plugin );
    if( loader )
    {
        d->plugins.insert( plugin, loader );
        d->pluginNames.insert( loader->metaData().value( "type" ).toString(), plugin );
        return loader->metaData();
    }

    return QJsonObject();
}

QList< QJsonObject > PluginRegistry::metaDataForType( const QString& type )
{
    QList< QJsonObject > list;

    if( d->pluginNames.contains( type ) )
    {
        for( auto name : d->pluginNames.values( type ) )
        {
            QJsonObject m = metaData( name );
            if( !m.isEmpty() )
                list.append( m );
        }
    }

    QList< QPluginLoader* > plugins = d->findPluginsByType( type );
    for( auto loader : plugins )
    {
        QString pluginName = QFileInfo( loader->fileName() ).baseName();
        if( !d->pluginNames.contains( pluginName ) )
        {
            list.append( loader->metaData() );
            d->plugins.insert( pluginName, loader );
            d->pluginNames.insert( type, pluginName );
        }
        else
        {
            delete loader;
        }
    }

    return list;
}

QObject* PluginRegistry::load( const QString& plugin )
{
    if( d->plugins.contains( plugin ) )
    {
        auto loader = d->plugins.value( plugin );
        if( !loader->isLoaded() )
        {
            if( !loader->load() )
            {
                WARNING() << d->plugins.value( plugin )->errorString();
            }
        }
        return loader->instance();
    }

    QPluginLoader* loader = d->findPlugin( plugin );
    if( loader )
    {
        d->plugins.insert( plugin, loader );
        d->pluginNames.insert( loader->metaData().value( "type" ).toString(), plugin );

        if( !loader->load() )
        {
            WARNING() << loader->errorString();
        }

        return loader->instance();
    }

    return nullptr;
}

QObjectList PluginRegistry::loadType( const QString& type )
{
    QObjectList list;

    if( d->pluginNames.contains( type ) )
    {
        for( auto name : d->pluginNames.values( type ) )
        {
            QObject* o = load( name );
            if( o )
                list.append( o );
        }
    }

    QList< QPluginLoader* > plugins = d->findPluginsByType( type );
    for( auto loader : plugins )
    {
        QString pluginName = QFileInfo( loader->fileName() ).baseName();
        if( !d->pluginNames.contains( pluginName ) )
        {
            if( loader->load() )
            {
                list.append( loader->instance() );
                d->plugins.insert( pluginName, loader );
                d->pluginNames.insert( type, pluginName );
            }
            else
            {
                WARNING() << loader->errorString();
            }
        }
        else
        {
            delete loader;
        }
    }

    return list;
}

QStringList PluginRegistry::pluginNamesForType( const QString& type )
{
    QStringList names;
    if( d->pluginNames.contains( type ) )
        names.append( d->pluginNames.values( type ) );

    QList< QPluginLoader* > plugins = d->findPluginsByType( type );
    for( auto loader : plugins )
    {
        QString pluginName = QFileInfo( loader->fileName() ).baseName();
        if( !d->pluginNames.contains( pluginName ) )
        {
            d->plugins.insert( pluginName, loader );
            d->pluginNames.insert( type, pluginName );
            names.append( pluginName );
        }
        else
        {
            delete loader;
        }
    }

    return names;
}

QStringList PluginRegistry::pluginDirectories()
{
    if( Private::pluginLocations.isEmpty() )
        Private::updatePluginDirectories();

    return Private::pluginLocations;
}

PluginRegistry::PluginRegistry(QObject* parent)
    : Singleton< GluonCore::PluginRegistry >(parent)
{
    d->q = this;
}

PluginRegistry::~PluginRegistry()
{
}

QPluginLoader*
PluginRegistry::Private::findPlugin( const QString& pluginName )
{
    if( pluginLocations.isEmpty() )
        updatePluginDirectories();

    DEBUG() << "Looking for plugin " << pluginName;

    for( auto location : pluginLocations )
    {
        QDir dir( location );
        dir.setFilter( QDir::AllEntries | QDir::NoDotAndDotDot );

        for( auto file : dir.entryInfoList( QDir::Files ) )
        {
            if( !QLibrary::isLibrary( file.absoluteFilePath() ) )
                continue;

            if( file.baseName() == pluginName )
            {
                QPluginLoader* loader = new QPluginLoader( file.absoluteFilePath(), q );
                if( loader->metaData().isEmpty() )
                {
                    WARNING() << "No metadata for plugin " << loader->fileName();
                    delete loader;
                    continue;
                }

                if( !loader->metaData().contains( "IID" ) )
                {
                    WARNING() << "Unable to determine type for plugin " << loader->fileName();
                    delete loader;
                    continue;
                }

                QString type = loader->metaData().value( "IID" ).toString();
                if( !knownTypes.contains( type ) )
                {
                    WARNING() << "Unknown type " << type << " of plugin " << loader->fileName();
                    delete loader;
                    continue;
                }

                return loader;
            }
        }
    }

    return nullptr;
}

QList< QPluginLoader* >
PluginRegistry::Private::findPluginsByType( const QString& type )
{
    if( pluginLocations.isEmpty() )
        updatePluginDirectories();

    QList< QPluginLoader* > loaders;

    DEBUG() << "Looking for plugins of type " << type;

    if( !knownTypes.contains( type ) )
    {
        WARNING() << "Trying to find unknown plugin type " << type;
        return loaders;
    }

    for( auto location : pluginLocations )
    {
        QDir dir( location );
        dir.setFilter( QDir::AllEntries | QDir::NoDotAndDotDot );

        for( auto file : dir.entryInfoList( QDir::Files ) )
        {
            if( !QLibrary::isLibrary( file.absoluteFilePath() ) )
                continue;

            if( plugins.contains(  file.baseName() ) )
                continue;

            QPluginLoader* loader = new QPluginLoader( file.absoluteFilePath(), q );
            if( loader->metaData().isEmpty() )
            {
                WARNING() << "No metadata for plugin " << loader->fileName();
                delete loader;
                continue;
            }

            if( !loader->metaData().contains( "IID" ) )
            {
                WARNING() << "Unable to determine type for plugin " << loader->fileName();
                delete loader;
                continue;
            }

            QString pluginType = loader->metaData().value( "IID" ).toString();
            if( !knownTypes.contains( pluginType ) )
            {
                WARNING() << "Unknown type " << pluginType << " of plugin " << loader->fileName();
                delete loader;
                continue;
            }

            if( pluginType != type )
            {
                delete loader;
                continue;
            }

            loaders.append( loader );
        }
    }

    DEBUG() << "Found " << loaders.count() << " new plugins.";

    return loaders;
}

void PluginRegistry::Private::updatePluginDirectories()
{
    pluginLocations.clear();

    QString location = QCoreApplication::applicationDirPath();

#if defined(Q_OS_WIN)
    if( location.endsWith(QLatin1String("/debug"), Qt::CaseInsensitive) )
    {
        location.chop(QByteArray("/debug").size());
    }
    else if( location.endsWith(QLatin1String("release"), Qt::CaseInsensitive) )
    {
        location.chop(QByteArray("/release").size());
    }

    if( QFile::exists( location + "/plugins" ) )
        pluginLocations.append( location + "/plugins" );
#elif defined(Q_OS_MAC)
    if( location.endsWith(QLatin1String("/MacOS")) )
        location.chop(QByteArray("/MacOS").size());

    if( QFile::exists( location + "/PlugIns" ) )
        pluginLocations.append( location + "/PlugIns" );
#endif

    QString libDir = DirectoryProvider::instance()->libDirectory();

    if( QFile::exists( libDir + "/gluon" ) )
        pluginLocations.append( libDir + "/gluon" );

    if( pluginLocations.isEmpty() )
    {
        CRITICAL() << "Could not find any sensible plugin directories!";
        abort();
    }

    DEBUG() << "Found " << pluginLocations.count() << " plugin locations.";
}
