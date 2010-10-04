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
#include <texture.h>
#include <game.h>

REGISTER_OBJECTTYPE(GluonEngine, SpriteRendererComponent)

using namespace GluonEngine;

class SpriteRendererComponent::SpriteRendererComponentPrivate
{
    public:
        SpriteRendererComponentPrivate()
        {
            item = 0;
            texture = 0;
            material = 0;
            size = QSizeF(1.0f, 1.0f);
            color.setRgb(255, 255, 255);
        }

        GluonGraphics::Item *item;
        GluonEngine::Asset* texture;
        GluonGraphics::MaterialInstance* material;

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
        d->item = GluonGraphics::Engine::instance()->createItem("default");
    }

    if (d->material)
    {
        d->material->material()->load(QUrl());
        Asset* texture = gameProject()->findChild<Asset*>(d->material->property("texture0").toString());
        if(texture)
            texture->load();
        d->item->setMaterialInstance(d->material);
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
        transform.scale(d->size.width()/2, d->size.height()/2);
        d->item->setTransform(transform);
    }
}

void SpriteRendererComponent::cleanup()
{
    if (d->item)
    {
        GluonGraphics::Engine::instance()->destroyItem(d->item);
        d->item = 0;
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

GluonGraphics::MaterialInstance*
SpriteRendererComponent::material()
{
    return d->material;
}

void
SpriteRendererComponent::setMaterial( GluonGraphics::MaterialInstance* material )
{
    if(!material)
        return;

    d->material = material;

    if(d->item)
        d->item->setMaterialInstance(material);
}

void
SpriteRendererComponent::setMaterial( const QString& path )
{
    setMaterial(qobject_cast<GluonGraphics::MaterialInstance*>(Game::instance()->gameProject()->findItemByName(path)));
}

Q_EXPORT_PLUGIN2(gluon_component_spriterenderer, GluonEngine::SpriteRendererComponent);

#include "spriterenderercomponent.moc"
