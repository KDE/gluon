/*****************************************************************************
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
 */

#include "backend.h"

#include <core/log.h>
#include <core/pluginregistry.h>

using namespace GluonGraphics;

Backend* Backend::m_backend = nullptr;

Backend* Backend::currentBackend()
{
    if( !m_backend )
        createBackend();

    return m_backend;
}

void Backend::createBackend()
{
    m_backend = qobject_cast< Backend* >( GluonCore::PluginRegistry::instance()->load( "gluongraphics_backend" ) );
    if( !m_backend )
    {
        CRITICAL() << "Could not load a backend for Gluon Graphics!";
        QCoreApplication::exit( 1 );
    }

    //Ensure we clean up the backend before any important resources are destroyed.
    QObject::connect( QCoreApplication::instance(), &QCoreApplication::aboutToQuit, []() { delete m_backend; }  );
}
