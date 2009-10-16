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

REGISTER_OBJECTTYPE(SpriteRenderComponent)

SpriteRenderComponent::SpriteRenderComponent ( QObject* parent ) : Component ( parent )
{
    d = new SpriteRenderComponentPrivate;
    #warning This really is not the way to fix this. Someone needs to take a
    #warning long, hard look at KGLItem - being unable to instantiate it
    #warning without a parent is pretty nasty
    //d->item = new KGLItem;
}

SpriteRenderComponent::SpriteRenderComponent ( const Gluon::SpriteRenderComponent& other )
    : Component ( other ),
    d(other.d)
{
    //d->item = new KGLItem;
}

SpriteRenderComponent::~SpriteRenderComponent()
{
    delete d->item;
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
    //Gluon::Component::Start();
}

void SpriteRenderComponent::Draw ( int timeLapse )
{
    //Gluon::Component::Draw ( timeLapse );
}

void Gluon::SpriteRenderComponent::setSize ( const QSizeF& size )
{
    d->size = size;
    //d->item->setSize(size);
}

QSizeF Gluon::SpriteRenderComponent::size()
{
    return d->size;
}
