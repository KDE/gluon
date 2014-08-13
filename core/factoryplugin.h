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

#ifndef GLUONCORE_FACTORYPLUGIN_H
#define GLUONCORE_FACTORYPLUGIN_H

#include <QObject>

#include <core/gluonobject.h>

namespace GluonCore
{
    class FactoryPlugin : public QObject
    {
        Q_OBJECT

    public:
        explicit FactoryPlugin( QObject* parent = 0 );
        virtual ~FactoryPlugin();

        virtual GluonObjectList typesToRegister() = 0;
    };
}

Q_DECLARE_INTERFACE( GluonCore::FactoryPlugin, "org.kde.gluon.core.factroyplugin" );

#define GLUONCORE_FACTORYPLUGIN \
    Q_INTERFACES( GluonCore::FactoryPlugin )\
    Q_PLUGIN_METADATA( IID "org.kde.gluon.core.factoryplugin" )

#define GLUONCORE_FACTORYPLUGIN_WITH_JSON( file )\
    Q_INTERFACES( GluonCore::FactoryPlugin )\
    Q_PLUGIN_METADATA( IID "org.kde.gluon.core.factoryplugin" FILE #file )

#endif // GLUONCORE_FACTORYPLUGIN_H
