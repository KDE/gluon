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

class QSizeF;
namespace GluonGraphics
{
    class MaterialInstance;
}

namespace GluonEngine
{
    class Asset;

    class GLUON_COMPONENT_ANIMATEDSPRITERENDERER_EXPORT AnimatedSpriteRendererComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::AnimatedSpriteRendererComponent )
            Q_INTERFACES( GluonEngine::Component )

            Q_PROPERTY( bool animate READ isAnimating WRITE setAnimating )
            Q_PROPERTY( bool loop READ isLooping WRITE setLooping )
            Q_PROPERTY( bool playing READ isPlaying )

            Q_PROPERTY( QSizeF size READ size WRITE setSize )
            Q_PROPERTY( GluonGraphics::MaterialInstance* material READ material WRITE setMaterial )
            Q_PROPERTY( int frameRate READ frameRate WRITE setFrameRate )
            Q_PROPERTY( int direction READ direction WRITE setDirection )
            Q_PROPERTY( QSizeF frameSize READ frameSize WRITE setFrameSize )
            Q_PROPERTY( QList<int> frameCounts READ frameCounts WRITE setFrameCounts )
            Q_PROPERTY( QList<int> startFrames READ startFrames WRITE setStartFrames )
            Q_PROPERTY( int animation READ animation WRITE setAnimation )
            //Q_PROPERTY( int textureCount READ textureCount WRITE setTextureCount )
            //Q_PROPERTY( QVector<Asset*> textures READ textures WRITE setTextures )

        public:
            Q_INVOKABLE AnimatedSpriteRendererComponent( QObject* parent = 0 );
            ~AnimatedSpriteRendererComponent();
            QString category() const;

            void initialize();
            void start();
            void update( int elapsedMilliseconds );
            void draw( int timeLapse = 0 );
            void stop();
            void cleanup();

            bool isAnimating();
            bool isLooping();
            bool isPlaying();

            QSizeF size();
            GluonGraphics::MaterialInstance* material();
            int frameRate();
            int direction();
            QSizeF frameSize();
            QList<int> frameCounts();
            QList<int> startFrames();
            int animation();
            //int textureCount();
            //virtual QVector<Asset*> textures();

        public slots:
            void setAnimating( bool animate );
            void setLooping( bool loop );
            void setSize( const QSizeF& size );
            void setMaterial( GluonGraphics::MaterialInstance* material );
            void setMaterial( const QString& path );
            void setFrameRate( int frameRate );
            void setDirection( int direction );
            void setFrameSize( const QSizeF& size );
            void setFrameCounts( const QList<int>& counts );
            void setStartFrames( const QList<int>& starts );
            void setAnimation( int anim );
            //void setTextureCount( int count );

        private:
            class Private;
            Private* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::AnimatedSpriteRendererComponent* )

#endif // GLUON_ENGINE_SPRITERENDERERCOMPONENT_H
