/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "resourcemanager.h"

#include "gluonobject.h"
#include "log.h"

using namespace GluonCore;

GLUON_DEFINE_SINGLETON( ResourceManager )

QByteArray ResourceManager::resourceIdentifierProperty = GluonObject::internalPropertyPrefix + "resource_identifier";

void ResourceManager::removeResource( QObject* resource )
{
    Q_ASSERT( resource );
    QString prefixedIdentifier = resource->property( resourceIdentifierProperty ).toString();
    if( !prefixedIdentifier.isEmpty() && m_resources.contains( prefixedIdentifier ) )
    {
        m_resources.remove( prefixedIdentifier );
    }
    else
    {
        NOTICE() << "Tried to remove object " << resource << " that is not known to ResourceManager";
    }
}

void ResourceManager::destroyResource( QObject* resource )
{
    Q_ASSERT( resource );
    QString prefixedIdentifier = resource->property( resourceIdentifierProperty ).toString();
    if( !prefixedIdentifier.isEmpty() && m_resources.contains( prefixedIdentifier ) )
    {
        QObject* resource = m_resources.value( prefixedIdentifier );
        m_resources.remove( prefixedIdentifier );
        resource->deleteLater();
    }
    else
    {
        NOTICE() << "Tried to destroy object " << resource->objectName() << " that is not known to ResourceManager";
    }
}

ResourceManager::ResourceManager( QObject* parent )
    : GluonCore::Singleton< ResourceManager >( parent )
{
}

ResourceManager::~ResourceManager()
{
}
