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

#ifndef GLUON_ENGINE_SPRITERENDERERCOMPONENT_H
#define GLUON_ENGINE_SPRITERENDERERCOMPONENT_H

#include <engine/gluon_engine_export.h>
#include <engine/component.h>

namespace GluonEngine
{
    class Asset;

    class GLUON_ENGINE_EXPORT SpriteRendererComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT(GluonEngine::SpriteRendererComponent)
            Q_PROPERTY(QSizeF size READ size WRITE setSize)
            Q_PROPERTY(QColor color READ color WRITE setColor)
            Q_PROPERTY(GluonEngine::Asset* texture READ texture WRITE setTexture)
            Q_INTERFACES(GluonEngine::Component)

        public:
            SpriteRendererComponent(QObject* parent = 0);
            SpriteRendererComponent(const SpriteRendererComponent& other);
            virtual ~SpriteRendererComponent();

            virtual void start();
            virtual void update(int elapsedMilliseconds);
            virtual void draw(int timeLapse = 0);
            virtual void stop();

            virtual QSizeF size();
            virtual QColor color();
            virtual Asset* texture();

        public slots:
            virtual void setSize(const QSizeF& size);
            virtual void setColor(const QColor& color);
            virtual void setColor(int r, int g, int b, int a = 255);
            virtual void setTexture(Asset* asset);

        private:
            class SpriteRendererComponentPrivate;
            SpriteRendererComponentPrivate *d;
    };

}

Q_DECLARE_METATYPE(GluonEngine::SpriteRendererComponent)
Q_DECLARE_METATYPE(GluonEngine::SpriteRendererComponent*)

#endif // GLUON_ENGINE_SPRITERENDERERCOMPONENT_H
