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

#include <engine/gluon_engine_export.h>
#include <engine/component.h>

class QSizeF;
namespace GluonGraphics
{
    class MaterialInstance;
}

namespace GluonEngine
{
    class Asset;

    class GLUON_COMPONENT_SPRITERENDERER_EXPORT AnimatedSpriteRendererComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::AnimatedSpriteRendererComponent )
            Q_INTERFACES( GluonEngine::Component )

            Q_PROPERTY( QSizeF size READ size WRITE setSize )
            Q_PROPERTY( GluonGraphics::MaterialInstance* material READ material WRITE setMaterial )
            Q_PROPERTY( int frameRate READ frameRate WRITE setFrameRate )
            Q_PROPERTY( int direction READ direction WRITE setDirection )
            Q_PROPERTY( bool oneTexturePerDirection READ hasOneTexturePerDirection WRITE setOneTexturePerDirection )
            Q_PROPERTY( QSizeF frameSize READ frameSize WRITE frameSize )
            Q_PROPERTY( QVector<int> frameCounts READ frameCounts WRITE setFrameCounts )
            Q_PROPERTY( QVector<int> startFrames READ startFrames WRITE setStartFrames )
            Q_PROPERTY( int textureCount READ textureCount WRITE setTextureCount )
            Q_PROPERTY( int currentAnimation READ currentAnimation WRITE setCurrentAnimation )
            //Q_PROPERTY( QVector<Asset*> textures READ textures WRITE setTextures )

        public:
            Q_INVOKABLE AnimatedSpriteRendererComponent( QObject* parent = 0 );
            ~AnimatedSpriteRendererComponent();
            QString category() const;

            void initialize();
            void start();
            void draw( int timeLapse = 0 );
            void cleanup();

            QSizeF size();
            GluonGraphics::MaterialInstance* material();
            int frameRate();
            int direction();
            QSizeF frameSize();
            QVector<int> frameCounts();
            QVector<int> startFrames();
            int textureCount();
            int currentAnimation();
            //virtual QVector<Asset*> textures();

        public slots:
            void setSize( const QSizeF& size );
            void setMaterial( GluonGraphics::MaterialInstance* material );
            void setMaterial( const QString& path );
            void setFrameRate( int frameRate );
            void setDirection( int direction );
            void setFrameSize( const QSizeF& size );
            void setFrameCounts( const QVector<int>& counts );
            void setStartFrames( const QVector<int>& starts );
            void setTextureCount( int count );
            void setCurrentAnimation( int anim );

        private:
            class SpriteRendererComponentPrivate;
            SpriteRendererComponentPrivate* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::SpriteRendererComponent )
Q_DECLARE_METATYPE( GluonEngine::SpriteRendererComponent* )

#endif // GLUON_ENGINE_SPRITERENDERERCOMPONENT_H
