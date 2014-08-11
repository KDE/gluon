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

#ifndef GLUONCORE_PLUGINREGISTRY_H
#define GLUONCORE_PLUGINREGISTRY_H

#include "singleton.h"
#include "privatepointer.h"

namespace GluonCore
{
    class PluginRegistry : public Singleton< PluginRegistry >
    {
        Q_OBJECT
        GLUON_SINGLETON( PluginRegistry )

        public:
            QJsonObject metaData( const QString& plugin );
            QList< QJsonObject > metaDataForType( const QString& type );

            QObject* load( const QString& plugin );
            QObjectList loadType( const QString& type );

            QStringList pluginNamesForType( const QString& type );

            static QStringList pluginDirectories();

        private:
            ~PluginRegistry();

            GLUON_PRIVATE_POINTER;
    };
}

#endif // GLUONCORE_PLUGINREGISTRY_H
