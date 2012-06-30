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
#include <QApplication>

#include <core/directoryprovider.h>
#include <core/debughelper.h>

#include "backend.h"
#include "world.h"
#include "rendertarget.h"
#include "material.h"
#include "spritemesh.h"
#include "texture.h"

using namespace GluonGraphics;

GLUON_DEFINE_SINGLETON( Manager );

class Manager::Private
{
    public:
        Private( Manager* qq ) : q( qq ), backend( 0 ) { }

        void createBackend();
        void aboutToQuit();

        Manager* q;

        Backend* backend;

        World* currentWorld;

        QHash< QString, World* > worlds;
};

const QString Manager::Defaults::World( "_defaultWorld" );
const QString Manager::Defaults::RenderTarget( "_defaultRenderTarget" );
const QString Manager::Defaults::Material( "_defaultMaterial" );
const QString Manager::Defaults::SpriteMesh( "_defaultSpriteMesh" );
const QString Manager::Defaults::Texture( "_defaultTexture" );
const char* Manager::resourceIdentifierProperty = "_GluonGraphics_ResourceIdentifier";

Backend* Manager::backend(  )
{
    if( !d->backend )
        d->createBackend();

    return d->backend;
}

void Manager::initialize()
{
    d->currentWorld = createWorld();
    SpriteMesh* defaultSpriteMesh = createResource< SpriteMesh >( Defaults::SpriteMesh );
    defaultSpriteMesh->initialize();
    createResource< Material >( Defaults::Material );
    Texture* defaultTexture = createResource< Texture >( Defaults::Texture );
    defaultTexture->load( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/defaults/default.png" );
    Material* defaultMaterial = createResource< Material >( Defaults::Material );
    defaultMaterial->load( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/defaults/default.gluonmaterial" );
    defaultMaterial->build();

    addResource< RenderTarget >( Defaults::RenderTarget, backend()->createRenderTarget() );
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
        delete world;
    }
}

World* Manager::currentWorld() const
{
    return d->currentWorld;
}

void Manager::setCurrentWorld( const QString& identifier )
{
    if( !d->worlds.contains( identifier ) )
        return;

    d->currentWorld = d->worlds.value( identifier );
    emit currentWorldChanged();
}

Manager::Manager( QObject* parent )
    : GluonCore::Singleton< Manager >( parent ), d( new Private( this ) )
{
    connect( QApplication::instance(), SIGNAL(aboutToQuit()), SLOT(aboutToQuit()) );
}

Manager::~Manager()
{
    delete d;
}

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

void Manager::Private::aboutToQuit()
{
    q->destroyWorld( Defaults::World );
    q->destroyResource< RenderTarget >( Defaults::RenderTarget );
    q->destroyResource< Material >( Defaults::Material );

    delete backend;
    qDeleteAll( worlds );
    qDeleteAll( q->m_resources );
}

#include "manager.moc"
