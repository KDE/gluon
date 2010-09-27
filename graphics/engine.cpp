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

#include <QtCore/QMutex>
#include <QtOpenGL/QGLFramebufferObject>

#include "camera.h"
#include "item.h"
#include "material.h"
#include "materialinstance.h"
#include "mesh.h"
#include "texture.h"
#include <core/gluon_global.h>

using namespace GluonGraphics;

template<> Engine *GluonCore::Singleton<Engine>::m_instance = 0;

class Engine::EnginePrivate
{
    public:
        EnginePrivate() : fbo(0), fboShader(0), camera(0) { }

        template <typename T>
        T* createObject( const QString& type, const QString& name, bool lock = true);

        void destroyObject(const QString& type, const QString& name);

        bool hasObject( const QString& type, const QString& name );

        template <typename T>
        T* object( const QString& type, const QString& name );

        bool addObject(const QString& type, const QString& name, QObject* value);

        void removeObject(const QString& type, const QString& name);

        QGLFramebufferObject * fbo;
        MaterialInstance * fboShader;

        Camera* camera;

        QVector<Item*> items;
        QHash<QString, QObject*> objects;

        QMutex mutex;

};

template <typename T> T*
Engine::EnginePrivate::createObject( const QString& type, const QString& name, bool lock )
{
    T * newObject;
    QString typeName = QString("%1/%2").arg(type, name);
    if(lock)
        mutex.lock();

    if(!objects.contains(typeName))
    {
        newObject = new T;
        objects.insert(typeName, newObject);
    }
    else
    {
        newObject = qobject_cast<T*>(objects.value(typeName));
    }

    if(lock)
        mutex.unlock();

    return newObject;
}

void
Engine::EnginePrivate::destroyObject( const QString& type, const QString& name )
{
    QString typeName = QString("%1/%2").arg(type, name);
    QMutexLocker locker(&mutex);

    if(objects.contains(typeName))
    {
        QObject* obj = objects.value(typeName);
        objects.remove(typeName);
        delete obj;
    }
}

bool
Engine::EnginePrivate::hasObject( const QString& type, const QString& name )
{
    QString typeName = QString("%1/%2").arg(type, name);
    QMutexLocker locker(&mutex);

    return objects.contains(typeName);
}

template <typename T> T*
Engine::EnginePrivate::object( const QString& type, const QString& name )
{
    QString typeName = QString("%1/%2").arg(type, name);
    QMutexLocker locker(&mutex);

    if(objects.contains(typeName))
        return qobject_cast<T*>(objects.value(typeName));

    return 0;
}

bool Engine::EnginePrivate::addObject( const QString& type, const QString& name, QObject* value )
{
    QString typeName = QString("%1/%2").arg(type, name);
    QMutexLocker locker(&mutex);

    if(!objects.contains(typeName))
    {
        objects.insert(typeName, value);
        return true;
    }

    return false;
}

void Engine::EnginePrivate::removeObject( const QString& type, const QString& name )
{
    QString typeName = QString("%1/%2").arg(type, name);
    QMutexLocker locker(&mutex);

    if(objects.contains(typeName))
        objects.remove(typeName);
}

void Engine::initialize()
{
    Material* material = createMaterial("default");
    material->build();

    Texture* tex = createTexture("default");
    tex->load(QUrl(GluonCore::Global::dataDirectory() + "/gluon/defaults/default.png"));

    Mesh* mesh = createMesh("default");
    mesh->load(QString());
    mesh->setMaterialInstance(material->createInstance());
    mesh->materialInstance()->setTexture(0, tex, "tex");
}

Item*
Engine::createItem( const QString& mesh)
{
    d->mutex.lock();

    Item * newItem = new Item(this);
    newItem->setMesh(d->createObject<Mesh>("Mesh", mesh, false));
    d->items << newItem;

    d->mutex.unlock();
    return newItem;
}

void
Engine::destroyItem( Item* item )
{
    d->mutex.lock();

    d->items.remove(d->items.indexOf(item));
    delete item;

    d->mutex.unlock();
}

Material*
Engine::createMaterial(const QString &name)
{
    Material * newMaterial = d->createObject<Material>("Material", name);
    newMaterial->setName(name);
    return newMaterial;
}

void Engine::destroyMaterial( const QString& name )
{
    d->destroyObject("Material", name);
}

bool Engine::hasMaterial( const QString& name )
{
    return d->hasObject("Material", name);
}

Material*
Engine::material( const QString& name )
{
    return d->object<Material>("Material", name);
}

bool
Engine::addMaterial( const QString& name, Material* material )
{
    return d->addObject("Material", name, material);
}

void
Engine::removeMaterial( const QString& name )
{
    d->removeObject("Material", name);
}

Mesh*
Engine::createMesh(const QString& name)
{
    return d->createObject<Mesh>("Mesh", name);
}

void
Engine::destroyMesh( const QString& name )
{
    d->destroyObject("Mesh", name);
}

bool
Engine::hasMesh( const QString& name )
{
    return d->hasObject("Mesh", name);
}

Mesh*
Engine::mesh( const QString& name )
{
    return d->object<Mesh>("Mesh", name);
}

bool
Engine::addMesh( const QString& name, Mesh* mesh )
{
    return d->addObject("Mesh", name, mesh);
}

void
Engine::removeMesh( const QString& name )
{
    d->removeObject("Mesh", name);
}

Texture*
Engine::createTexture(const QString& name)
{
    return d->createObject<Texture>("Texture", name);
}

void
Engine::destroyTexture( const QString& name )
{
    d->destroyObject("Texture", name);
}

bool
Engine::hasTexture( const QString& name )
{
    return d->hasObject("Texture", name);
}

Texture*
Engine::texture( const QString& name )
{
    return d->object<Texture>("Texture", name);
}

bool
Engine::addTexture( const QString& name, Texture* texture )
{
    return d->addObject("Texture", name, texture);
}

void
Engine::removeTexture( const QString& name )
{
    d->removeObject("Texture", name);
}

Camera*
Engine::activeCamera()
{
    return d->camera;
}

void
Engine::render()
{
    d->mutex.lock();

    //Bind the framebuffer object so we render to it.
    //d->fbo->bind();

    //Walk through all items, rendering them as we go
    const int size = d->items.size();
    for(int i = 0; i < size; ++i)
    {
        d->items.at(i)->render();
    }

    //Unbind the FBO, making us stop rendering to it.
    //d->fbo->release();

    //Render a full screen quad with the FBO data.
    //d->fboShader->bind();
    //glDrawArrays(GL_TRIANGLES, );
    //d->fboShader->release();

    d->mutex.unlock();
}

void
Engine::setFramebufferSize( int width, int height )
{
    d->mutex.lock();

    delete d->fbo;
    d->fbo = new QGLFramebufferObject(width, height, QGLFramebufferObject::Depth);

    d->mutex.unlock();
}

void Engine::setActiveCamera( Camera* camera )
{
    d->mutex.lock();
    d->camera = camera;
    d->mutex.unlock();
    emit activeCameraChanged(camera);
}

Engine::Engine()
    : d(new EnginePrivate())
{
}

Engine::~Engine()
{
    delete d->fbo;
    delete d;
}

#include "engine.moc"
