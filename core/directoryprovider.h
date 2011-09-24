/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#ifndef GLUON_CORE_DIRECTORYPROVIDER_H
#define GLUON_CORE_DIRECTORYPROVIDER_H

#include "gluon_core_export.h"
#include "core/gluon_global.h"

#include "singleton.h"

#include <QtCore/QHash>

namespace GluonCore
{

    class GLUON_CORE_EXPORT DirectoryProvider : public Singleton<DirectoryProvider>
    {
            Q_OBJECT
            GLUON_SINGLETON( DirectoryProvider )

        public:

            /**
             * Returns a directory location which is the prefix for other
             * installation locations, like data, library, user and the like.
             * The method will ensure that the installation happens by cmake or
             * other installation methods, like Windows Installer. It will
             * pick up the proper path prefix accordingly.
             *
             * @return  The installation prefix
             */
            QString installPrefix() const;

            /**
             * Returns the directory location where the project data is installed
             * to, and can also be stored.
             *
             * @return  The data directory location
             */
            QString dataDirectory() const;

            /**
             * Returns the directory location where the libraries are installed
             * to.
             *
             * @return  The library directory location
             */
            QString libDirectory() const;

            /**
             * Returns the desired user directory location inside the location where
             * persistent application data can be stored. The method will ensure
             * that the path is created properly, if it is a new location.
             *
             * @param name  The identifier of the desired directory location
             * @return      The desired user directory location
             */
            QString userDirectory( const QString& name );

            /**
             * Returns the directory locations where plugins can be found.
             *
             * @return  The list of the plugin directory locations
             */
            QStringList pluginDirectoryPaths() const;

        private:
            class DirectoryProviderPrivate;
            DirectoryProviderPrivate *const d;
    };

}

#endif // GLUON_CORE_DIRECTORYPROVIDER_H
