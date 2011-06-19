/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "engine.h"

#ifdef Q_OS_WIN
#include <windows.h>
#include <GL/glee.h>
#endif

#include "camera.h"
#include "item.h"
#include "material.h"
#include "materialinstance.h"
#include "mesh.h"
#include "texture.h"
#include "viewport.h"
#include "rendertarget.h"

#include <core/gluon_global.h>

#include <QtCore/QMutex>
#include <QtCore/QMutableListIterator>

using namespace GluonGraphics;

GLUON_DEFINE_SINGLETON( Engine )

class Engine::EnginePrivate
{
    public:
        EnginePrivate() : mainTarget( 0 ), mainTargetShader( 0 ), camera( 0 ), viewport( 0 ) { }

        template <typename T>
        T* createObject( const QString& type, const QString& name );

        void destroyObject( const QString& type, const QString& name );

        bool hasObject( const QString& type, const QString& name );

        template <typename T>
        T* object( const QString& type, const QString& name );

        bool addObject( const QString& type, const QString& name, QObject* value );

        void removeObject( const QString& type, const QString& name );

        void viewportSizeChanged( int left, int bottom, int width, int height );

        RenderTarget* mainTarget;
        MaterialInstance* mainTargetShader;

        QList<QWeakPointer<RenderTarget> > renderTargets;

        Camera* camera;
        Viewport* viewport;

        QVector<Item*> items;
        QHash<QString, QObject*> objects;

        QMutex objectMutex;
        QMutex itemMutex;

};

template <typename T> T*
Engine::EnginePrivate::createObject( const QString& type, const QString& name )
{
    T* newObject;
    QString typeName = QString( "%1/%2" ).arg( type, name );

    objectMutex.lock();

    if( objects.contains( typeName ) )
    {
        newObject = qobject_cast<T*>( objects.value( typeName ) );
    }
    else
    {
        newObject = new T;
        objects.insert( typeName, newObject );
    }

    objectMutex.unlock();

    return newObject;
}

void
Engine::EnginePrivate::destroyObject( const QString& type, const QString& name )
{
    QString typeName = QString( "%1/%2" ).arg( type, name );
    QMutexLocker locker( &objectMutex );

    if( objects.contains( typeName ) )
    {
        QObject* obj = objects.value( typeName );
        objects.remove( typeName );
        delete obj;
    }
}

bool
Engine::EnginePrivate::hasObject( const QString& type, const QString& name )
{
    QString typeName = QString( "%1/%2" ).arg( type, name );

    return objects.contains( typeName );
}

template <typename T> T*
Engine::EnginePrivate::object( const QString& type, const QString& name )
{
    QString typeName = QString( "%1/%2" ).arg( type, name );

    if( objects.contains( typeName ) )
        return qobject_cast<T*>( objects.value( typeName ) );

    return 0;
}

bool Engine::EnginePrivate::addObject( const QString& type, const QString& name, QObject* value )
{
    QString typeName = QString( "%1/%2" ).arg( type, name );
    QMutexLocker locker( &objectMutex );

    if( !objects.contains( typeName ) )
    {
        objects.insert( typeName, value );
        return true;
    }

    return false;
}

void Engine::EnginePrivate::removeObject( const QString& type, const QString& name )
{
    QString typeName = QString( "%1/%2" ).arg( type, name );
    QMutexLocker locker( &objectMutex );

    if( objects.contains( typeName ) )
        objects.remove( typeName );
}

void Engine::EnginePrivate::viewportSizeChanged( int left, int bottom, int width, int height )
{
    if( mainTarget )
        mainTarget->resize( width, height );

    for( QList<QWeakPointer<RenderTarget> >::iterator target = renderTargets.begin();
            target != renderTargets.end(); ++target )
    {
        if( *target )
        {
            (*target).data()->resize( width, height );
        }
    }
}

void Engine::initialize()
{
    Material* material = createMaterial( "default" );
    material->load( GluonCore::Global::dataDirectory() + "/gluon/defaults/default.gml" );
    material->build();
    material->instance( "default" )->setProperty( "materialColor", Qt::white );
    material->instance( "default" )->setProperty( "texture0", QString( "default" ) );

    Texture* tex = createTexture( "default" );
    tex->load( QUrl( GluonCore::Global::dataDirectory() + "/gluon/defaults/default.png" ) );

    Mesh* mesh = createMesh( "default" );
    mesh->load( QString() );

    d->mainTarget = new RenderTarget( 1024, 768, this );
    d->mainTarget->setMaterialInstance( material->createInstance( "mainTarget" ) );
}

Item*
Engine::createItem( const QString& mesh )
{
    QMutexLocker locker( &d->itemMutex );

    Item* newItem = new Item( this );
    newItem->setMesh( d->createObject<Mesh>( "Mesh", mesh ) );
    d->items << newItem;

    return newItem;
}

void
Engine::addItem( Item* item )
{
    QMutexLocker locker( &d->itemMutex );

    d->items << item;
}

void
Engine::destroyItem( Item* item )
{
    QMutexLocker locker( &d->itemMutex );

    d->items.remove( d->items.indexOf( item ) );
    delete item;
}

Material*
Engine::createMaterial( const QString& name )
{
    Material* newMaterial = d->createObject<Material>( "Material", name );
    newMaterial->setName( name );
    return newMaterial;
}

void Engine::destroyMaterial( const QString& name )
{
    d->destroyObject( "Material", name );
}

bool Engine::hasMaterial( const QString& name )
{
    return d->hasObject( "Material", name );
}

Material*
Engine::material( const QString& name )
{
    return d->object<Material>( "Material", name );
}

bool
Engine::addMaterial( const QString& name, Material* material )
{
    return d->addObject( "Material", name, material );
}

void
Engine::removeMaterial( const QString& name )
{
    d->removeObject( "Material", name );
}

Mesh*
Engine::createMesh( const QString& name )
{
    return d->createObject<Mesh>( "Mesh", name );
}

void
Engine::destroyMesh( const QString& name )
{
    d->destroyObject( "Mesh", name );
}

bool
Engine::hasMesh( const QString& name )
{
    return d->hasObject( "Mesh", name );
}

Mesh*
Engine::mesh( const QString& name )
{
    return d->object<Mesh>( "Mesh", name );
}

bool
Engine::addMesh( const QString& name, Mesh* mesh )
{
    return d->addObject( "Mesh", name, mesh );
}

void
Engine::removeMesh( const QString& name )
{
    d->removeObject( "Mesh", name );
}

Texture*
Engine::createTexture( const QString& name )
{
    return d->createObject<Texture>( "Texture", name );
}

void
Engine::destroyTexture( const QString& name )
{
    d->destroyObject( "Texture", name );
}

bool
Engine::hasTexture( const QString& name )
{
    return d->hasObject( "Texture", name );
}

Texture*
Engine::texture( const QString& name )
{
    return d->object<Texture>( "Texture", name );
}

bool
Engine::addTexture( const QString& name, Texture* texture )
{
    return d->addObject( "Texture", name, texture );
}

void
Engine::removeTexture( const QString& name )
{
    d->removeObject( "Texture", name );
}

Camera*
Engine::activeCamera()
{
    return d->camera;
}

Viewport*
Engine::currentViewport()
{
    return d->viewport;
}

RenderTarget* Engine::mainRenderTarget()
{
    return d->mainTarget;
}

void
Engine::addRenderTarget( RenderTarget* target, int depth )
{
    if( !d->renderTargets.contains( target ) )
    {
        d->renderTargets.insert( depth, QWeakPointer<RenderTarget>( target ) );
    }
}

void
Engine::render()
{
    if( !d->camera )
        return;

    d->objectMutex.lock();

    //Bind the framebuffer object so we render to it.
    d->mainTarget->bind();

    //Walk through all items, rendering them as we go
    const int size = d->items.size();
    for( int i = 0; i < size; ++i )
    {
        d->items.at( i )->render();
    }

    //Unbind the FBO, making us stop rendering to it.
    d->mainTarget->release();

    glDisable( GL_DEPTH_TEST );

    //Render a full screen quad with the FBO data.
    d->mainTarget->render();

    QMutableListIterator<QWeakPointer<RenderTarget> > i(d->renderTargets);
    while (i.hasNext())
    {
        QWeakPointer<RenderTarget> target = i.next();
        if( target )
        {
            target.data()->render();
        }
        else
        {
            i.remove();
        }
    }
    glEnable( GL_DEPTH_TEST );

    d->objectMutex.unlock();
}

void
Engine::setActiveCamera( Camera* camera )
{
    emit activeCameraChanging( camera );
    d->objectMutex.lock();
    d->camera = camera;
    d->objectMutex.unlock();
}

void
Engine::setViewport( Viewport* viewport )
{
    emit currentViewportChanging( viewport );
    d->objectMutex.lock();
    d->viewport = viewport;
    connect( d->viewport, SIGNAL( viewportSizeChanged( int, int, int, int ) ), this, SLOT( viewportSizeChanged( int, int, int, int ) ) );
    d->objectMutex.unlock();
}

Engine::Engine()
    : d( new EnginePrivate() )
{
    setViewport( new Viewport() );
    connect( this, SIGNAL( activeCameraChanging( Camera* ) ), d->viewport, SLOT( update() ) );
}

Engine::~Engine()
{
    delete d;
}

#include "engine.moc"
