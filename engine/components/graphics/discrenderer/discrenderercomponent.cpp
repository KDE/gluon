/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
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
#include "discrenderercomponent.h"

#include "graphics/meshes/discmesh.h"
#include "graphics/item.h"
#include "engine/gameobject.h"
#include "engine/asset.h"
#include <QMimeData>
//#include <sys/stat.h>

REGISTER_OBJECTTYPE(GluonEngine, DiscRendererComponent)

using namespace GluonEngine;

class DiscRendererComponent::DiscRendererComponentPrivate
{
    public:
        DiscRendererComponentPrivate()
        {
            item = 0;
            mesh = 0;
            texture = 0;
            nbPoints = 3;
            radius = 5.0f;
            color.setRgb(255, 255, 255);
        }

        GluonGraphics::Item *item;
        GluonGraphics::DiscMesh *mesh;
        
        GluonEngine::Asset* texture;

        uint nbPoints;
        float radius;
        QColor color;
};

DiscRendererComponent::DiscRendererComponent(QObject* parent) 
    : Component(parent),
    d(new DiscRendererComponentPrivate)
{
    
}

DiscRendererComponent::DiscRendererComponent(const DiscRendererComponent& other)
    : Component(other),
    d(other.d)
{
}

DiscRendererComponent::~DiscRendererComponent()
{
    delete d;
}

void DiscRendererComponent::initialize()
{
    if(!d->item)
    {
        d->mesh = new GluonGraphics::DiscMesh(this->gameObject()->position(), d->radius, d->nbPoints,d->color,this);
        d->item = new GluonGraphics::Item(d->mesh, this);
        d->item->setColor(d->color);
    }

    if (d->texture)
    {
        if (!d->texture->isLoaded())
            d->texture->load();

        const QMimeData* data = d->texture->data();
        if (data->hasImage())
        {
            d->mesh->setTexture(data->imageData().value<QImage>());
        }
    }
}

void DiscRendererComponent::start()
{
}

void DiscRendererComponent::draw(int timeLapse)
{
    Q_UNUSED(timeLapse)

    if (d->item)
    {
        d->item->setMatrix(gameObject()->transform());
    }
}

void DiscRendererComponent::cleanup()
{
    if (d->item)
    {
        delete d->item;
        d->item = 0;
        d->mesh = 0;
    }
}

float DiscRendererComponent::radius()
{
    return d->radius;
}

void DiscRendererComponent::setRadius(float newRadius)
{
    d->radius = newRadius;
    if(this->gameObject())
        this->setDisc(this->gameObject()->position(), d->radius, d->nbPoints, d->color);
}

uint DiscRendererComponent::nbPoints()
{
    return d->nbPoints;
}

void DiscRendererComponent::setNbPoints(uint newNbPoints)
{
    d->nbPoints = newNbPoints;
    if(this->gameObject())
        this->setDisc(this->gameObject()->position(), d->radius, d->nbPoints, d->color);
}

void DiscRendererComponent::setDisc(QVector3D position, float radius, uint nbPoints, QColor color)
{
    if(d->mesh)
        d->mesh->setDisc(position, radius, nbPoints, color);
}

void DiscRendererComponent::setColor(const QColor& color)
{
    d->color = color;
    if (d->mesh)
    {
        d->mesh->setColor(color);
    }
}

void DiscRendererComponent::setColor(int r, int g, int b, int a)
{
    setColor(QColor(r, g, b, a));
}

QColor DiscRendererComponent::color()
{
    return d->color;
}

Asset* DiscRendererComponent::texture()
{
    return d->texture;
}

void DiscRendererComponent::setTexture(Asset* asset)
{
    d->texture = asset;

    if (asset)
    {
        if (d->mesh && asset->isLoaded())
        {
            d->mesh->setTexture(asset->data()->imageData().value<QImage>());
        }
    }
}

Q_EXPORT_PLUGIN2(gluon_component_discrenderer, GluonEngine::DiscRendererComponent);

#include "discrenderercomponent.moc"