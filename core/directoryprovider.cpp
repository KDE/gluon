/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include <QtCore/QDir>
#include <QtGui/QDesktopServices>
#include <QtCore/QCoreApplication>

using namespace GluonCore;

GLUON_DEFINE_SINGLETON(DirectoryProvider)

DirectoryProvider::DirectoryProvider(QObject* parent)
{
    m_userDirNames[UserDataDir] = "data";
    m_userDirNames[UserGamesDir] = "games";
}

QString DirectoryProvider::installPrefix()
{
    return GLUON_INSTALL_PREFIX;
}

QString DirectoryProvider::dataDirectory()
{
    return GLUON_SHARE_INSTALL_DIR;
}

QString DirectoryProvider::libDirectory()
{
    return GLUON_LIB_INSTALL_DIR;
}

QString DirectoryProvider::userDir(DirectoryProvider::UserDir dir)
{
    if(m_userDir.isEmpty()) {
        m_userDir = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
        m_userDir.remove(QCoreApplication::applicationName());
        m_userDir.remove(QCoreApplication::organizationName());
        QDir dataLocation(m_userDir);

        //Create the user dirs
        foreach(QString subDir, m_userDirNames.values()) {
            dataLocation.mkpath("gluon/" + subDir);
        }

        m_userDir = dataLocation.absoluteFilePath("gluon/");
    }

    return QDir::fromNativeSeparators(m_userDir + "/" + m_userDirNames[dir]);
}
