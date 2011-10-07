/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include "directoryprovider.h"

#include <QtGui/QDesktopServices>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QSettings>
#include <QtCore/QCoreApplication>

using namespace GluonCore;

GLUON_DEFINE_SINGLETON( DirectoryProvider )

class DirectoryProvider::DirectoryProviderPrivate
{
    public:
        DirectoryProviderPrivate()
        {
        }

        ~DirectoryProviderPrivate()
        {
        }

        QString userDataPath;
        QHash<QString, QString> userDirs;
};

DirectoryProvider::DirectoryProvider( QObject* parent )
    : GluonCore::Singleton< GluonCore::DirectoryProvider >( parent )
    , d( new DirectoryProviderPrivate )
{
    d->userDataPath = QDesktopServices::storageLocation( QDesktopServices::DataLocation );
    d->userDataPath.chop( QString(QCoreApplication::organizationName() + '/' + QCoreApplication::applicationName()).size() );
    d->userDataPath.append( "gluon" );

    // Define standard dirs Gluon recommends
    d->userDirs["data"] =  QDir::fromNativeSeparators( d->userDataPath + "/data" );
    d->userDirs["games"] = QDir::fromNativeSeparators( d->userDataPath + "/games" );

    // Create standard dirs Gluon recommends
    QDir dir;
    foreach( const QString& dirPath, d->userDirs )
    {
        dir.mkpath( dirPath );
    }
}

QString DirectoryProvider::installPrefix() const
{
#ifdef Q_OS_WIN
    QSettings *settings;
    if (GLUON_ARCHITECTURE == "32")
        settings = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Gluon\\Gluon-" + GLUON_VERSION_STRING + "\\", QSettings::NativeFormat);
    else if (GLUON_ARCHITECTURE == "64")
        settings = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Gluon\\Gluon-" + GLUON_VERSION_STRING + "\\", QSettings::NativeFormat);

    QString installPath = settings->value("Default").toString();
    delete settings;
    return installPath.isEmpty() ? GLUON_INSTALL_PREFIX : installPath;
#else
    return GLUON_INSTALL_PREFIX;
#endif
}

QString DirectoryProvider::dataDirectory() const
{
    return installPrefix() + '/' + GLUON_SHARE_INSTALL_DIR;
}

QString DirectoryProvider::libDirectory() const
{
    return installPrefix() + '/' + GLUON_LIB_INSTALL_DIR;
}

QString DirectoryProvider::userDirectory( const QString& name )
{
    if( !d->userDirs.contains( name ) )
    {
        QString path = QDir::fromNativeSeparators( d->userDataPath + name );
        d->userDirs[name] = path;
        QDir dir;
        dir.mkpath( path );
    }

    return d->userDirs[name];
}

QStringList DirectoryProvider::pluginDirectoryPaths() const
{
    QStringList pluginDirectoryPaths;

    QString pluginDirectoryPath = QCoreApplication::applicationDirPath();

#if defined(Q_OS_WIN)
    if( pluginDirectoryPath.endsWith(QLatin1String("/debug"), Qt::CaseInsensitive) )
        pluginDirectoryPath.chop(QByteArray("/debug").size());

    else if( pluginDirectoryPath.endsWith(QLatin1String("release"), Qt::CaseInsensitive) )
        pluginDirectoryPath.chop(QByteArray("/release").size());

#elif defined(Q_OS_MAC)
    if( pluginDirectoryPath.endsWith(QLatin1String("/MacOS")) )
        pluginDirectoryPath.chop(QByteArray("/MacOS").size());

#endif

    if( QFile( pluginDirectoryPath + "/PlugIns" ).exists() )
        pluginDirectoryPaths.append( pluginDirectoryPath );

    QString libraryDirectoryPath = libDirectory();

    if( QFile( libraryDirectoryPath ).exists() )
        pluginDirectoryPaths.append( libraryDirectoryPath );

    // This is the plugin dir on windows
    if( QFile( libraryDirectoryPath + "/kde4" ).exists() )
        pluginDirectoryPaths.append( libraryDirectoryPath + "/kde4" );

    if( QFile( libraryDirectoryPath + "/gluon" ).exists() )
        pluginDirectoryPaths.append( libraryDirectoryPath + "/gluon" );

    if( QFile( QDir::homePath() + "/gluonplugins" ).exists() )
        pluginDirectoryPaths.append( QDir::homePath() + "/gluonplugins" );

    return pluginDirectoryPaths;
}

#include "directoryprovider.moc"
