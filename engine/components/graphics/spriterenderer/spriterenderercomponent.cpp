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

REGISTER_OBJECTTYPE(GluonEngine, SpriteRendererComponent)

Q_DECLARE_METATYPE(GluonCore::GluonObject*);

using namespace GluonEngine;

class SpriteRendererComponent::SpriteRendererComponentPrivate
{
    public:
        SpriteRendererComponentPrivate() { item = 0; }

        GluonGraphics::Item *item;
};

SpriteRendererComponent::SpriteRendererComponent ( QObject* parent ) : Component ( parent )
{
    d = new SpriteRendererComponentPrivate;

    QVariant somethingEmpty;
    Asset *theObject = 0;
    somethingEmpty.setValue<GluonCore::GluonObject*>(theObject);
    setProperty("texture", somethingEmpty);
}

SpriteRendererComponent::SpriteRendererComponent ( const SpriteRendererComponent& other )
    : Component ( other ),
    d(other.d)
{
}

SpriteRendererComponent::~SpriteRendererComponent()
{
    delete d->item;
    delete d;
}

GluonCore::GluonObject* SpriteRendererComponent::instantiate()
{
    return new SpriteRendererComponent(this);
}

void SpriteRendererComponent::start()
{
    DEBUG_FUNC_NAME;
    if(!d->item) d->item = new GluonGraphics::Item(QSizeF(1.f, 1.f));
    if(texture()) {
        DEBUG_TEXT("We have a texture!");
        QMimeData* data = texture()->data();
        if(data->hasImage()) {
            DEBUG_TEXT("Setting item texture...");
            d->item->setTexture(data->imageData().value<QImage>());
        } else {
            DEBUG_TEXT("Boo! We dont have image data.");
            DEBUG_TEXT(QString("Instead we have: %1").arg(data->formats().join(" ")));
        }
    }
}

void SpriteRendererComponent::draw ( int timeLapse )
{
    Q_UNUSED(timeLapse)

    d->item->resetTransform();
    d->item->applyTransform(gameObject()->transform());
}

void SpriteRendererComponent::update ( int elapsedMilliseconds )
{
    Q_UNUSED(elapsedMilliseconds)
}

void SpriteRendererComponent::setSize ( const QSizeF &size )
{
    //d->item->setSize(size);
}

QSizeF SpriteRendererComponent::size()
{
    //return d->item->size();
}

void SpriteRendererComponent::setColor(const QColor& color)
{
    if(d->item) {
        d->item->setColor(color);
    }
}

QColor SpriteRendererComponent::color()
{
    if(d->item) {
        return d->item->color();
    }
    return QColor();
}

Asset* SpriteRendererComponent::texture()
{
    GluonObject* obj = property("texture").value<GluonCore::GluonObject*>();
    return qobject_cast<Asset*>(obj);
}

void SpriteRendererComponent::setTexture(Asset* asset)
{
    QVariant theNewValue;
    theNewValue.setValue<GluonCore::GluonObject*>(asset);
    setProperty("texture", theNewValue);
}

Q_EXPORT_PLUGIN2(gluon_component_spriterenderer, GluonEngine::SpriteRendererComponent);

#include "spriterenderercomponent.moc"
