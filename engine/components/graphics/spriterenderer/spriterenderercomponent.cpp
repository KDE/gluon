/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "spriterenderercomponent.h"

#include <graphics/item.h>
#include <gameobject.h>
#include <core/debughelper.h>

#include <iostream>
#include <asset.h>
#include <QMimeData>

#include <graphics/meshes/polygonmesh.h>
#include <graphics/meshes/spritemesh.h>

REGISTER_OBJECTTYPE(GluonEngine, SpriteRendererComponent)

Q_DECLARE_METATYPE(GluonCore::GluonObject*);
Q_DECLARE_METATYPE(GluonEngine::Asset*);

using namespace GluonEngine;

class SpriteRendererComponent::SpriteRendererComponentPrivate
{
    public:
        SpriteRendererComponentPrivate()
        {
            item = 0;
            mesh = 0;
            size.setHeight(1.0f);
            size.setWidth(1.0f);
            color.setRgb(255, 255, 255);
        }

        GluonGraphics::Item *item;
        GluonGraphics::SpriteMesh *mesh;

        QColor color;
        QSizeF size;
};

SpriteRendererComponent::SpriteRendererComponent ( QObject* parent ) : Component ( parent )
{
    d = new SpriteRendererComponentPrivate;

    QVariant somethingEmpty;
    Asset *theObject = 0;
    somethingEmpty.setValue<GluonEngine::Asset*>(theObject);
    setProperty("texture", somethingEmpty);
}

SpriteRendererComponent::SpriteRendererComponent ( const SpriteRendererComponent& other )
    : Component ( other ),
    d(other.d)
{
}

SpriteRendererComponent::~SpriteRendererComponent()
{
    stop();

    delete d;
}

void SpriteRendererComponent::start()
{
    if(!d->item) {
        d->mesh = new GluonGraphics::SpriteMesh(d->size);
        d->item = new GluonGraphics::Item(d->mesh);
        d->item->setColor(d->color);
    }

    if(texture()) {
        if(!texture()->isLoaded())
            texture()->load();

        const QMimeData* data = texture()->data();
        if(data->hasImage()) {
            d->item->mesh()->setTexture(data->imageData().value<QImage>());
        }
    }
}

void SpriteRendererComponent::draw ( int timeLapse )
{
    Q_UNUSED(timeLapse)

    if(d->item) {
        d->item->setMatrix(gameObject()->transform());
    }
}

void SpriteRendererComponent::update ( int elapsedMilliseconds )
{
    Q_UNUSED(elapsedMilliseconds)
}

void SpriteRendererComponent::stop()
{
    if(d->item) {
        delete d->item;
        delete d->mesh;
        d->item = 0;
        d->mesh = 0;
    }
}

void SpriteRendererComponent::setSize ( const QSizeF &size )
{
    d->size = size;

    if(d->mesh) {
        d->mesh->setSize(size);
    }
}

QSizeF SpriteRendererComponent::size()
{
    return d->size;
}

void SpriteRendererComponent::setColor(const QColor& color)
{
    d->color = color;
    if(d->mesh) {
        d->mesh->setColor(color);
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
    GluonObject* obj = property("texture").value<GluonCore::GluonObject*>();
    return qobject_cast< GluonEngine::Asset* >(obj);
}

void SpriteRendererComponent::setTexture(Asset* asset)
{
    QVariant somethingEmpty;
    somethingEmpty.setValue<GluonEngine::Asset*>(asset);
    setProperty("texture", somethingEmpty);
}

Q_EXPORT_PLUGIN2(gluon_component_spriterenderer, GluonEngine::SpriteRendererComponent);

#include "spriterenderercomponent.moc"
