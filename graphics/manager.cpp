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
#include <QtCore/QPluginLoader>

#include <core/directoryprovider.h>
#include <core/debughelper.h>

#include "backend.h"
#include "world.h"

using namespace GluonGraphics;

GLUON_DEFINE_SINGLETON( Manager );

#define PREFIX_IDENTIFIER(Object, Identifier) QString( "%1::%2" ).arg( Object->metaObject()->className() ).arg( Identifier );

class Manager::Private
{
    public:
        Private() : backend( 0 ) { }
        void createBackend();
        Backend* backend;

        QHash< QString, World* > worlds;
        QHash< QString, QObject* > resources;
};

const QString Manager::defaultWorld( "_defaultWorld" );
const QString Manager::defaultRenderTarget( "_defaultRenderTarget" );

Backend* Manager::backend(  )
{
    if( !d->backend )
        d->createBackend();

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

World* Manager::currentWorld() const
{

}

void Manager::setCurrentWorld( const QString& identifier )
{

}

void Manager::addResource( const QString& identifier, QObject* object )
{
    QString prefixedIdentifier = PREFIX_IDENTIFIER( object, identifier );
    DEBUG_FUNC_NAME
    DEBUG_TEXT( prefixedIdentifier );
    if( !d->resources.contains( prefixedIdentifier ) )
        d->resources.insert( prefixedIdentifier, object );
}

void Manager::removeResource( QObject* resource )
{

}

QObject* Manager::resource( const QString& identifier )
{

}

Manager::Manager( QObject* parent )
    : GluonCore::Singleton< Manager >( parent ), d( new Private )
{

}

Manager::~Manager()
{
    delete d->backend;
    qDeleteAll( d->worlds );
    qDeleteAll( d->resources );
}

// T* Manager::createResource( const QString& identifier )
// {
//     DEBUG_FUNC_NAME
//     QString prefixedIdentifier = PREFIX_IDENTIFIER( T, identifier );
//     DEBUG_TEXT( prefixedIdentifier );
//     if( d->resources.contains( prefixedIdentifier ) )
//         return qobject_cast< T* >( d->resources.value( prefixedIdentifier ) );
//
//     T* newResource = new T( this );
//     d->resources.insert( prefixedIdentifier, newResource );
//
//     return newResource;
// }
//
// template < typename T >
// void Manager::addResource( const QString& identifier, T* object )
// {
//     QString prefixedIdentifier = PREFIX_IDENTIFIER( T, identifier );
//     if( !d->resources.contains( prefixedIdentifier ) )
//         d->resources.insert( prefixedIdentifier, object );
// }
//
// template < typename T >
// T* Manager::resource( const QString& identifier ) const
// {
//     QString prefixedIdentifier = PREFIX_IDENTIFIER( T, identifier );
//     if( d->resources.contains( prefixedIdentifier ) )
//         return qobject_cast< T*>( d->resources.value( prefixedIdentifier ) );
//
//     return 0;
// }
//
// template < typename T >
// void Manager::destroyResource( const QString& identifier )
// {
//     QString prefixedIdentifier = PREFIX_IDENTIFIER( T, identifier );
//     QObject* resource = d->resources.value( prefixedIdentifier );
//     if( resource )
//     {
//         d->resources.remove( prefixedIdentifier );
//         resource->deleteLater();
//     }
// }

void Manager::Private::createBackend()
{
    QString pluginPath = GluonCore::DirectoryProvider::instance()->libDirectory() + "/gluon/gluongraphics_backend.so";
    QPluginLoader loader( pluginPath );
    if( !loader.load() )
    {
        qFatal( loader.errorString().toUtf8().data() );
    }

    backend = qobject_cast< Backend*>( loader.instance() );
    if( !backend )
        qFatal( "The backend plugin %s does not provide a GluonGraphics::Backend object!", pluginPath.toUtf8().data() );
}

#include "manager.moc"
