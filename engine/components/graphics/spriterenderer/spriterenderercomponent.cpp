/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "spriterenderercomponent.h"

#include <core/debughelper.h>
#include <graphics/item.h>
#include <graphics/engine.h>
#include <graphics/material.h>
#include <graphics/spritemesh.h>
#include <graphics/materialinstance.h>
#include <engine/gameobject.h>
#include <engine/asset.h>

#include <QtCore/QMimeData>
#include <QtCore/QVariant>
#include <QtGui/QMatrix4x4>
#include <QtGui/QColor>

REGISTER_OBJECTTYPE(GluonEngine, SpriteRendererComponent)

using namespace GluonEngine;

class SpriteRendererComponent::SpriteRendererComponentPrivate
{
    public:
        SpriteRendererComponentPrivate()
        {
            item = 0;
            texture = 0;
            size = QSizeF(1.0f, 1.0f);
            color.setRgb(255, 255, 255);
        }

        GluonGraphics::Item *item;
        //GluonGraphics::SpriteMesh *mesh;

        GluonEngine::Asset* texture;

        QColor color;
        QSizeF size;
};

SpriteRendererComponent::SpriteRendererComponent(QObject* parent)
    : Component(parent),
    d(new SpriteRendererComponentPrivate)
{

}

SpriteRendererComponent::SpriteRendererComponent(const SpriteRendererComponent& other)
    : Component(other),
    d(other.d)
{
}

SpriteRendererComponent::~SpriteRendererComponent()
{
    delete d;
}

QString
SpriteRendererComponent::category() const
{
    return QString("Graphics Rendering");
}

void
SpriteRendererComponent::initialize()
{
    if(!d->item)
    {
        if(!GluonGraphics::Engine::instance()->hasMesh("default"))
        {
            GluonGraphics::Mesh* sprite = new GluonGraphics::Mesh(GluonGraphics::Engine::instance());
            sprite->load(QString());
            GluonGraphics::Material * material = GluonGraphics::Engine::instance()->createMaterial("default");
            material->build();
            sprite->setMaterial(material->createInstance());
            GluonGraphics::Engine::instance()->addMesh("default", sprite);
        }

        d->item = GluonGraphics::Engine::instance()->createItem("default");
        d->item->mesh()->setMaterial(GluonGraphics::Engine::instance()->material("default")->createInstance());
        d->item->mesh()->materialInstance()->setUniform("materialColor", d->color);
    }

    if (d->texture)
    {
        if (!d->texture->isLoaded())
            d->texture->load();

        const QMimeData* data = d->texture->data();
        if (data->hasImage())
        {
            //d->mesh->setTexture(data->imageData().value<QImage>());
        }
    }
}

void
SpriteRendererComponent::start()
{
}

void SpriteRendererComponent::draw(int timeLapse)
{
    Q_UNUSED(timeLapse)

    if (d->item)
    {
        QMatrix4x4 transform = gameObject()->transform();
        transform.scale(d->size.width(), d->size.height());
        d->item->setTransform(transform);
    }
}

void SpriteRendererComponent::cleanup()
{
    if (d->item)
    {
        GluonGraphics::Engine::instance()->destroyItem(d->item);
        d->item = 0;
        //d->mesh = 0;
    }
}

void SpriteRendererComponent::setSize(const QSizeF &size)
{
    d->size = size;
}

QSizeF SpriteRendererComponent::size()
{
    return d->size;
}

void SpriteRendererComponent::setColor(const QColor& color)
{
    d->color = color;
    if (d->item)
    {
        d->item->mesh()->materialInstance()->setUniform("materialColor", color);
    }
}

void SpriteRendererComponent::setColor(int r, int g, int b, int a)
{
    setColor(QColor(r, g, b, a));
}

QColor SpriteRendererComponent::color()
{
    return d->color;
}

Asset* SpriteRendererComponent::texture()
{
    return d->texture;
}

void SpriteRendererComponent::setTexture(Asset* asset)
{
    d->texture = asset;

    if (asset)
    {
        /*if (d->mesh && asset->isLoaded())
        {
            d->mesh->setTexture(asset->data()->imageData().value<QImage>());
        }*/
    }
}

Q_EXPORT_PLUGIN2(gluon_component_spriterenderer, GluonEngine::SpriteRendererComponent);

#include "spriterenderercomponent.moc"
