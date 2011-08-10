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
            QString installPrefix() const;

            QString dataDirectory() const;

            QString libDirectory() const;

            QString userDirectory( const QString& name );

        private:
            QString m_userDataPath;
            QHash<QString, QString> m_userDirs;
    };

}

#endif // GLUON_CORE_DIRECTORYPROVIDER_H
