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
#include "spriterenderercomponentprivate.h"

#include <graphics/item.h>
#include <gameobject.h>

REGISTER_OBJECTTYPE(GluonEngine, SpriteRendererComponent)

using namespace GluonEngine;

SpriteRendererComponent::SpriteRendererComponent ( QObject* parent ) : Component ( parent )
{
    d = new SpriteRendererComponentPrivate;
    d->item = new GluonGraphics::Item(QSizeF(1.f, 1.f));
}

SpriteRendererComponent::SpriteRendererComponent ( const SpriteRendererComponent& other )
    : Component ( other ),
    d(other.d)
{
    d->item = new GluonGraphics::Item(other.d->size);
}

SpriteRendererComponent::~SpriteRendererComponent()
{

}

GluonCore::GluonObject* SpriteRendererComponent::instantiate()
{
    return new SpriteRendererComponent(this);
}

void SpriteRendererComponent::Update ( int elapsedMilliseconds )
{
    Q_UNUSED(elapsedMilliseconds)

    Eigen::Vector3f position = gameObject()->position();
    d->item->setPosition(position.x(), position.y());
    d->item->setZIndex(position.z());

    Eigen::Vector3f scale = gameObject()->scale();
    d->item->setScale(scale.x(), scale.y());

    d->item->setAngle(gameObject()->rotation());
}

void SpriteRendererComponent::Start()
{
}

void SpriteRendererComponent::Draw ( int timeLapse )
{
    Q_UNUSED(timeLapse)
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
    d->item->setColor(color);
}

QColor SpriteRendererComponent::color()
{
    return d->item->color();
}

Q_EXPORT_PLUGIN2(gluon_component_spriterenderer, GluonEngine::SpriteRendererComponent);

#include "spriterenderercomponent.moc"
