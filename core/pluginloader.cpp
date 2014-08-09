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

#include "pluginloader.h"

#include <QtCore/QFile>
#include <QtCore/QPluginLoader>
#include <QtCore/QStringList>
#include <QtCore/QDir>

#include "debughelper.h"
#include "directoryprovider.h"

using namespace GluonCore;

class PluginLoader::Private
{
    public:
        void updatePluginLocations();

        QString pluginName;

        static QStringList pluginLocations;
};

QStringList PluginLoader::Private::pluginLocations;

PluginLoader::PluginLoader( const QString& pluginName, QObject* parent )
    : QObject( parent )
{
    d->pluginName = pluginName;
}

PluginLoader::~PluginLoader()
{
}

QObject* PluginLoader::load( QObject* parent )
{
    if( Private::pluginLocations.isEmpty() )
        d->updatePluginLocations();

    for( const QString& location : Private::pluginLocations )
    {
        QDir dir( location );
        dir.setFilter( QDir::AllEntries | QDir::NoDotAndDotDot );
        for( const QString& file : dir.entryList( QDir::Files ) )
        {
            if( !file.startsWith( "gluon" ) )
                continue;

            if( !QLibrary::isLibrary( dir.absoluteFilePath( file ) ) )
                continue;

            if( file.endsWith( d->pluginName + ".so" ) )
            {
                QPluginLoader loader( dir.absoluteFilePath( file ) );
                loader.load();

                if( loader.isLoaded() )
                {
                    QObject* instance = loader.instance();
                    instance->setParent( parent );
                    return instance;
                }
                else
                {
                    DEBUG_BLOCK
                    DEBUG_TEXT2( "Plugin failed to load: %1", loader.errorString() );
                }
            }
        }
    }

    return nullptr;
}

void PluginLoader::Private::updatePluginLocations()
{
    pluginLocations.clear();

    QString pluginDirectoryPath = QCoreApplication::applicationDirPath();

#if defined(Q_OS_WIN)

    if( pluginDirectoryPath.endsWith(QLatin1String("/debug"), Qt::CaseInsensitive) )
        pluginDirectoryPath.chop(QByteArray("/debug").size());

    else if( pluginDirectoryPath.endsWith(QLatin1String("release"), Qt::CaseInsensitive) )
        pluginDirectoryPath.chop(QByteArray("/release").size());

    if( QFile::exists( pluginDirectoryPath + "/plugins" ) )
        pluginLocations.append( pluginDirectoryPath );

#elif defined(Q_OS_MAC)

    if( pluginDirectoryPath.endsWith(QLatin1String("/MacOS")) )
        pluginDirectoryPath.chop(QByteArray("/MacOS").size());

    if( QFile::exists( pluginDirectoryPath + "/PlugIns" ) )
        pluginLocations.append( pluginDirectoryPath );

#endif

    QString libraryDirectoryPath = DirectoryProvider::instance()->libDirectory();

    if( QFile::exists( libraryDirectoryPath ) )
        pluginLocations.append( libraryDirectoryPath );

    if( QFile::exists( libraryDirectoryPath + "/gluon" ) )
        pluginLocations.append( libraryDirectoryPath + "/gluon" );
}
