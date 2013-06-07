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

#ifndef GLUON_ENGINE_SPRITERENDERERCOMPONENT_H
#define GLUON_ENGINE_SPRITERENDERERCOMPONENT_H

#include <engine/component.h>

#include <QSizeF>

namespace GluonGraphics
{
    class MaterialInstance;
}

namespace GluonEngine
{
    class Asset;

    class SpriteRendererComponent : public Component
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Component )
            GLUON_OBJECT( GluonEngine::SpriteRendererComponent )

            Q_PROPERTY( QSizeF size READ size WRITE setSize )
            Q_PROPERTY( GluonGraphics::MaterialInstance* material READ material WRITE setMaterial )

            Q_CLASSINFO( "org.gluon.category", "Graphics Rendering" )
            Q_CLASSINFO( "org.gluon.icon", "image-x-generic" )

        public:
            Q_INVOKABLE SpriteRendererComponent( QObject* parent = 0 );
            virtual ~SpriteRendererComponent();
            virtual QString category() const;

            virtual void initialize();
            virtual void start();
            virtual void draw( int timeLapse = 0 );
            virtual void cleanup();
            virtual GluonCore::AxisAlignedBox boundingBox();

            virtual QSizeF size();
            virtual GluonGraphics::MaterialInstance* material();

        public Q_SLOTS:
            virtual void setSize( const QSizeF& size );
            virtual void setMaterial( GluonGraphics::MaterialInstance* material );
            virtual void setMaterial( const QString& path );
            virtual void setEnabled( bool newEnabled );

        private:
            class SpriteRendererComponentPrivate;
            SpriteRendererComponentPrivate* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::SpriteRendererComponent* )

#endif // GLUON_ENGINE_SPRITERENDERERCOMPONENT_H
