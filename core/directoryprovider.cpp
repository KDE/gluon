/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

using namespace GluonCore;

GLUON_DEFINE_SINGLETON( DirectoryProvider )

DirectoryProvider::DirectoryProvider( QObject* parent )
{
    m_userDataPath = QDesktopServices::storageLocation( QDesktopServices::DataLocation );
    m_userDataPath.remove( QCoreApplication::applicationName() );
    m_userDataPath.remove( QCoreApplication::organizationName() );
    m_userDataPath.append( "/gluon/" );

    //Define standard dirs Gluon recommends
    m_userDirs["data"] =  QDir::fromNativeSeparators( m_userDataPath + "/data" );
    m_userDirs["games"] = QDir::fromNativeSeparators( m_userDataPath + "/games" );

    //Create standard dirs Gluon recommends
    QDir dir;
    foreach( const QString& dirPath, m_userDirs )
    {
        dir.mkpath( dirPath );
    }
}

QString DirectoryProvider::installPrefix() const
{
#ifdef Q_OS_WIN
    QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Gluon\\Gluon-" + GLUON_VERSION_STRING + "\\", QSettings::NativeFormat);
    QString installPath = settings.value("Default").toString();
    return installPath.isEmpty() ? GLUON_INSTALL_PREFIX : installPath;
#else
    return GLUON_INSTALL_PREFIX;
#endif
}

QString DirectoryProvider::dataDirectory() const
{
    return installPrefix() + "/" + GLUON_SHARE_INSTALL_DIR;
}

QString DirectoryProvider::libDirectory() const
{
    return installPrefix() + "/" + GLUON_LIB_INSTALL_DIR;
}

QString DirectoryProvider::userDirectory( const QString& name )
{
    if( !m_userDirs.contains( name ) )
    {
        QString path = QDir::fromNativeSeparators( m_userDataPath + name );
        m_userDirs[name] = path;
        QDir dir;
        dir.mkpath( path );
    }

    return m_userDirs[name];
}

#include "directoryprovider.moc"
