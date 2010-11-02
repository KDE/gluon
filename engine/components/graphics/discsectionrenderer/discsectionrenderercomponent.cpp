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

#include "discsectionrenderercomponent.h"

#include "graphics/meshes/discsectionmesh.h"
#include "graphics/item.h"
#include "engine/gameobject.h"
#include "engine/asset.h"

#include <QMimeData>

#include <cmath>

REGISTER_OBJECTTYPE(GluonEngine, DiscSectionRendererComponent)

using namespace GluonEngine;

class DiscSectionRendererComponent::DiscSectionRendererComponentPrivate
{
    public:
        DiscSectionRendererComponentPrivate()
        {
            item = 0;
            mesh = 0;
            texture = 0;
            nbPoints = 3;
            radius = 5.0f;
            degrees  = 90.0f;
            arcCenter = M_PI / 2.0f;
            color.setRgb(255, 255, 255);
        }

        GluonGraphics::Item *item;
        GluonGraphics::DiscSectionMesh *mesh;

        GluonEngine::Asset *texture;

        uint nbPoints;
        float radius;
        float degrees;
        float arcCenter;
        QColor color;
};

DiscSectionRendererComponent::DiscSectionRendererComponent(QObject *parent)
    : Component(parent)
    , d(new DiscSectionRendererComponentPrivate)
{

}

DiscSectionRendererComponent::DiscSectionRendererComponent(const DiscSectionRendererComponent &other)
    : Component(other)
    , d(other.d)
{
}

DiscSectionRendererComponent::~DiscSectionRendererComponent()
{
    delete d;
}

QString
DiscSectionRendererComponent::category() const
{
    return QString("Graphics Rendering");
}

void DiscSectionRendererComponent::initialize()
{
    if (!d->item) {
        d->mesh = new GluonGraphics::DiscSectionMesh(gameObject()->position(), d->radius, d->nbPoints, d->degrees, d->arcCenter, d->color, this);
        d->item = new GluonGraphics::Item(d->mesh, this);
        d->item->setColor(d->color);
    }

    if (d->texture) {
        if (!d->texture->isLoaded())
            d->texture->load();

        const QMimeData *data = d->texture->data();
        if (data->hasImage()) {
            d->mesh->setTexture(data->imageData().value<QImage>());
        }
    }
}

void DiscSectionRendererComponent::start()
{
}

void DiscSectionRendererComponent::draw(int timeLapse)
{
    Q_UNUSED(timeLapse)

    if (d->item) {
        d->item->setMatrix(gameObject()->transform());
    }
}

void DiscSectionRendererComponent::cleanup()
{
    if (d->item) {
        delete d->item;
        d->item = 0;
        d->mesh = 0;
    }
}

float DiscSectionRendererComponent::radius()
{
    return d->radius;
}

void DiscSectionRendererComponent::setRadius(float newRadius)
{
    d->radius = newRadius;
    if (gameObject())
        setDiscSection(gameObject()->position(), d->radius, d->nbPoints, d->degrees, d->arcCenter, d->color);
}

uint DiscSectionRendererComponent::nbPoints()
{
    return d->nbPoints;
}

void DiscSectionRendererComponent::setNbPoints(uint newNbPoints)
{
    d->nbPoints = newNbPoints;
    if (gameObject())
        setDiscSection(gameObject()->position(), d->radius, d->nbPoints, d->degrees, d->arcCenter, d->color);
}

void DiscSectionRendererComponent::setDiscSection(QVector3D position, float radius, uint nbPoints, float degrees, float arcCenter,QColor color)
{
    if (d->mesh)
        d->mesh->setDiscSection(position, radius, nbPoints, degrees, arcCenter, color);
}

float DiscSectionRendererComponent::degrees()
{
    return d->degrees;
}

void DiscSectionRendererComponent::setDegrees(float newDegrees)
{
    if (newDegrees > 359.9f) {
        d->degrees = 359.9f;
    } else if (newDegrees == 0) {
        d->degrees = 1;
    } else {
        d->degrees = newDegrees;
    }

    if (gameObject())
        setDiscSection(gameObject()->position(), d->radius, d->nbPoints, d->degrees, d->arcCenter, d->color);
}

void DiscSectionRendererComponent::setColor(const QColor& color)
{
    d->color = color;
    if (d->mesh) {
        d->mesh->setColor(color);
    }
}

void DiscSectionRendererComponent::setColor(int r, int g, int b, int a)
{
    setColor(QColor(r, g, b, a));
}

QColor DiscSectionRendererComponent::color()
{
    return d->color;
}

Asset* DiscSectionRendererComponent::texture()
{
    return d->texture;
}

void DiscSectionRendererComponent::setTexture(Asset* asset)
{
    d->texture = asset;

    if (asset) {
        if (d->mesh && asset->isLoaded()) {
            d->mesh->setTexture(asset->data()->imageData().value<QImage>());
        }
    }
}

float DiscSectionRendererComponent::arcCenter()
{
    return d->arcCenter * (180.0f/M_PI);
}

void DiscSectionRendererComponent::setArcCenter(float newArcCenter)
{
    if(newArcCenter > 359.9f) {
       newArcCenter = 359.9f;
    } else if(newArcCenter == 0) {
        newArcCenter = 1;
    } else {
        newArcCenter = newArcCenter;
    }

    d->arcCenter = newArcCenter * (M_PI/180.0f);

    if (gameObject())
        setDiscSection(gameObject()->position(), d->radius, d->nbPoints, d->degrees, d->arcCenter, d->color);
}

Q_EXPORT_PLUGIN2(gluon_component_discsectionrenderer, GluonEngine::DiscSectionRendererComponent);

#include "discsectionrenderercomponent.moc"
