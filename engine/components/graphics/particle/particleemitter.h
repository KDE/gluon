/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUON_ENGINE_PARTICLEEMITTER_H
#define GLUON_ENGINE_PARTICLEEMITTER_H

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

    class GLUON_COMPONENT_PARTICLEEMITTER_EXPORT ParticleEmitterComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::ParticleAnimatorComponent )
            Q_INTERFACES( GluonEngine::Component )

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
            Q_INVOKABLE ParticleEmitterComponent( QObject* parent = 0 );
            ~ParticleEmitterComponent();

            QString category() const;

            void initialize();
            void start();
            void update( int elapsedMilliseconds );
            void draw( int timeLapse = 0 );
            void cleanup();

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

Q_DECLARE_METATYPE( GluonEngine::ParticleEmitterComponent* )

#endif // GLUON_ENGINE_PARTICLEEMITTER_H
