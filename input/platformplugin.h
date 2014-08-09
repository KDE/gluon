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

#ifndef GLUONINPUT_PLATFORMPLUGIN_H
#define GLUONINPUT_PLATFORMPLUGIN_H

#include <QtCore/QObject>
#include <QtCore/QList>

namespace GluonInput
{
    class PlatformPlugin : public QObject
    {
        Q_OBJECT

        public:
            explicit PlatformPlugin( QObject* parent = 0 ) : QObject( parent ) { }
            virtual ~PlatformPlugin() { }

            virtual void initialize() = 0;
            virtual QStringList listDevices() = 0;

        Q_SIGNALS:
            void deviceAdded( const QString& plugin );
            void deviceRemoved( const QString& plugin );
    };
}

Q_DECLARE_INTERFACE( GluonInput::PlatformPlugin, "org.kde.gluon.input.platform" )

#define GLUONINPUT_PLATFORMPLUGIN \
    Q_INTERFACES( GluonInput::PlatformPlugin )\
    Q_PLUGIN_METADATA( IID "org.kde.gluon.input.platform" )

#endif // GLUONINPUT_PLATFORMPLUGIN_H
