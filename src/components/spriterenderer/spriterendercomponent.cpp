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

#include "spriterendercomponent.h"
#include "spriterendercomponentprivate.h"

#include <kgl/kglitem.h>

using namespace Gluon;

SpriteRenderComponent::SpriteRenderComponent ( QObject* parent ) : Component ( parent )
{
    d = new SpriteRenderComponentPrivate;
}

SpriteRenderComponent::SpriteRenderComponent ( const Gluon::SpriteRenderComponent& other ) : Component ( other )
{
    d = new SpriteRenderComponentPrivate(other.d);
}

GluonObject* SpriteRenderComponent::instantiate()
{
    return new SpriteRenderComponent(this);
}

void SpriteRenderComponent::Update ( int elapsedMilliseconds )
{

}

void SpriteRenderComponent::Start()
{
    Gluon::Component::Start();
}

void SpriteRenderComponent::Draw ( int timeLapse )
{
    Gluon::Component::Draw ( timeLapse );
}

void Gluon::SpriteRenderComponent::setSize ( const QSizeF& size )
{
    d->size = size;
}

QSizeF Gluon::SpriteRenderComponent::size()
{
    return d->size;
}
