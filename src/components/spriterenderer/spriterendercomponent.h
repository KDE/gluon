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

#ifndef GLUON_SPRITERENDERCOMPONENT_H
#define GLUON_SPRITERENDERCOMPONENT_H

#include <gameproject/component.h>
#include <kgl/kglitem.h>

namespace Gluon
{

class SpriteRenderComponentPrivate;

class SpriteRenderComponent : public Component
{
    Q_OBJECT

    Q_PROPERTY(QSizeF size READ size WRITE setSize)
    
    public:
        SpriteRenderComponent ( QObject* parent = 0 );
        SpriteRenderComponent ( const SpriteRenderComponent& other);

        virtual GluonObject* instantiate();
        
        virtual void Update ( int elapsedMilliseconds );
        virtual void Start();
        virtual void Draw ( int timeLapse = 0 );

        virtual QSizeF size();

    public slots:
        virtual void setSize(const QSizeF& size);
        
    private:
        QSharedDataPointer<SpriteRenderComponentPrivate> d;
};

REGISTER_OBJECTTYPE(SpriteRenderComponent)
}

#endif // GLUON_SPRITERENDERCOMPONENT_H
