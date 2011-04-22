/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef GLUON_ENGINE_PARTICLERENDERER_H
#define GLUON_ENGINE_PARTICLERENDERER_H

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

    class GLUON_COMPONENT_PARTICLERENDERER_EXPORT ParticleRendererComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::ParticleRendererComponent )
            Q_INTERFACES( GluonEngine::Component )

            Q_PROPERTY( bool castShadows READ castShadows WRITE setCastShadows )

            Q_PROPERTY( bool receiveShadows READ receiveShadows WRITE setReceiveShadows )

            Q_PROPERTY( QSizeF size READ size WRITE setSize )

            // Reference to a list of Materials that will be displayed in the position of each individual particle.
            Q_PROPERTY( GluonGraphics::MaterialInstance* material READ material WRITE setMaterial )

            // The amount of stretching that is applied to the Particles based on
            // Camera movement.
            Q_PROPERTY( int cameraVelocityScale READ cameraVelocityScale WRITE setCameraVelocityScale )

            // Determines how the particles are rendered.
            Q_PROPERTY( StretchParticles stretchParticles READ stretchParticles WRITE setStretchParticles )

            // If Stretch Particles is set to Stretched, this value determines
            // how long the particles are in their direction of motion.
            Q_PROPERTY( int lengthScale READ lengthScale WRITE setLengthScale )

            // If Stretch Particles is set to Stretched, this value determines
            // the rate at which particles will be stretched, based on their
            // movement speed.
            Q_PROPERTY( int velocityScale READ velocityScale WRITE setVelocityScale )

            // Number of frames located across the X axis.
            Q_PROPERTY( int uvAnimationXTile READ uvAnimationXTile WRITE setUVAnimationXTile )

            // Number of frames located across the Y axis.
            Q_PROPERTY( int uvAnimationYTile READ uvAnimationYTile WRITE setUVAnimationYTile )

            // How many times to loop the animation sequence.
            Q_PROPERTY( int uvAnimationCycles READ uvAnimationCycles WRITE setUVAnimationCycles )

        public:
            enum StretchParticles
            {
                // The particles are rendered as if facing the camera.
                Billboard,
                // The particles are facing the direction they are moving.
                Stretched,
                // The particles are sorted by depth. Use this when using a
                // blending material.
                SortedBillboard,
                // All particles are aligned flat along the X/Z axes.
                VerticalBillboard,
                // All particles are aligned flat along the X/Y axes.
                HorizontalBillboard,
            };

            Q_INVOKABLE ParticleRendererComponent( QObject* parent = 0 );
            ~ParticleRendererComponent();

            QString category() const;

            void initialize();
            void start();
            void update( int elapsedMilliseconds );
            void draw( int timeLapse = 0 );
            void cleanup();

            GluonGraphics::MaterialInstance* material();

            bool castShadows();
            bool receiveShadows();
            QSizeF size();
            GluonGraphics::MaterialInstance* material();
            int cameraVelocityScale();
            StretchParticles stretchParticles();
            int lengthScale();
            int velocityScale();
            int uvAnimationXTile();
            int uvAnimationYTile();
            int uvAnimationCycles();

        public slots:
            void setCastShadows( bool castShadows );
            void setReceiveShadows( bool receiveShadows );
            void setSize( const QSizeF& size );
            void setMaterial( GluonGraphics::MaterialInstance* material );
            void setMaterial( const QString& path );
            void setCameraVelocity( int cameraVelocity );
            void setStretchParticles( StretchParticles stretchParticles );
            void setLengthScale( int lengthScale );
            void setVelocityScale( int velocityScale );
            void setUVAnimationXTile( int uvAnimationXTile );
            void setUVAnimationYTile( int uvAnimationYTile );
            void setUVAnimationCycle( int uvAnimationCycles );

        private:
            class Private;
            Private* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::ParticleRendererComponent* )

#endif // GLUON_ENGINE_PARTICLERENDERER_H
