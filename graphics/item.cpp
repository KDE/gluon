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

#include "item.h"

#include <QtGui/QMatrix4x4>

#include <core/debughelper.h>

#include "mesh.h"
#include "camera.h"
#include "frustum.h"
#include "engine.h"
#include "math.h"

using namespace GluonGraphics;

class Item::ItemPrivate
{
    public:
        ItemPrivate() { materialInstance = 0; }
        Mesh * mesh;
        QMatrix4x4 transform;
        MaterialInstance* materialInstance;
};

Item::Item(QObject * parent)
        : QObject(parent),
          d(new ItemPrivate)
{
}

Item::~Item()
{
    delete d;
}

Mesh*
Item::mesh()
{
    return d->mesh;
}

QMatrix4x4
Item::transform()
{
    return d->transform;
}

MaterialInstance*
Item::materialInstance()
{
    return d->materialInstance;
}

void
Item::render()
{
    Camera* activeCam = Engine::instance()->activeCamera();

    #ifdef __GNUC__
    #warning ToDo: Implement view frustum culling. After all, that is what that damn class is for... ;)
    #endif

    QMatrix4x4 modelViewProj = Math::calculateModelViewProj(d->transform, activeCam->viewMatrix(), activeCam->frustum()->projectionMatrix());

    if(d->materialInstance)
        d->mesh->setMaterialInstance(d->materialInstance);
    d->mesh->render(modelViewProj);
}

void
Item::setTransform( const QMatrix4x4 transform )
{
    d->transform = transform;
}

void
Item::setMesh( Mesh* mesh )
{
    d->mesh = mesh;
}

MaterialInstance*
Item::setMaterialInstance(MaterialInstance * instance)
{
    d->materialInstance = instance;
}


#include "item.moc"
