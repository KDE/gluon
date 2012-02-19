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

#include "manager.h"

#include <QtCore/QHash>

#include "backend.h"
#include "world.h"

using namespace GluonGraphics;

GLUON_DEFINE_SINGLETON( Manager );

Backend* createBackend( QObject* parent );

class Manager::Private
{
    public:
        Backend* backend;

        QHash< QString, World* > worlds;
        QHash< QString, QObject* > resources;
};

const QString Manager::defaultWorldIdentifier("_default");

Backend* Manager::backend()
{
    if( !d->backend )
        d->backend = createBackend( this );

    return d->backend;
}

World* Manager::createWorld( const QString& identifier )
{
    if( d->worlds.contains( identifier ) )
        return d->worlds.value( identifier );

    World* newWorld = new World( this );
    d->worlds.insert( identifier, newWorld );

    return newWorld;
}

World* Manager::world( const QString& identifier ) const
{
    return d->worlds.value( identifier );
}

void Manager::destroyWorld( const QString& identifier )
{
    World* world = d->worlds.value( identifier );

    if( world )
    {
        d->worlds.remove( identifier );
        world->deleteLater();
    }
}

template <typename T>
T* Manager::createResource( const QString& identifier )
{
    if( d->resources.contains( identifier ) )
        return qobject_cast< T* >( d->resources.value( identifier ) );

    T* newResource = new T( this );
    d->resources.insert( identifier, newResource );

    return newResource;
}

// template < Texture >
// Texture* Manager::createResource( const QString& identifier )
// {
//     if( d->resources.contains( identifier ) )
//         return qobject_cast< Texture* >( d->resources.value( identifier ) );
//
//     Texture* newTexture = d->ba
// }

template< typename T>
Manager* Manager::resource( const QString& identifier ) const
{
    if( d->resources.contains( identifier ) )
        return qobject_cast< T*>( d->resources.value( identifier ) );

    return 0;
}

void Manager::destroyResource( const QString& identifier )
{
    QObject* resource = d->resources.value( identifier );
    if( resource )
    {
        d->resources.remove( identifier );
        resource->deleteLater();
    }
}

Manager::Manager( QObject* parent )
    : GluonCore::Singleton< Manager >( parent ), d( new Private )
{

}

Manager::~Manager()
{
    qDeleteAll( d->worlds );
    qDeleteAll( d->resources );
}

#ifdef Q_WS_X11
    #include "glx/glxbackend.h"
    Backend* createBackend( QObject* parent ) { return new GLXBackend( parent ); }
#else
    #error GluonGraphics: Your current windowing system is not supported!
#endif