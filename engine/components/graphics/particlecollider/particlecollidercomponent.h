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

#ifndef GLUON_ENGINE_PARTICLECOLLIDERCOMPONENT_H
#define GLUON_ENGINE_PARTICLECOLLIDERCOMPONENT_H

#include <engine/component.h>

class QSizeF;
namespace GluonGraphics
{
    class MaterialInstance;
}

namespace GluonEngine
{
    class Asset;

    class GLUON_COMPONENT_PARTICLECOLLIDER_EXPORT ParticleColliderComponent : public Component
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::ParticleColliderComponent )
            Q_INTERFACES( GluonEngine::Component )

            // Particles can be accelerated or slowed down when they collide
            // against other objects. This factor is similar to the Particle
            // Animator's Damping property.
            Q_PROPERTY( float bounceFactor READ bounceFactor WRITE setBounceFactor )

            // Amount of energy (in seconds) a particle should lose when
            // colliding. If the energy goes below 0, the particle is killed.
            Q_PROPERTY( int collisionEnergyLoss READ collisionEnergyLoss WRITE setCollisionEnergyLoss )

            // If a particle's Velocity drops below Min Kill Velocity because of a collision, it will be eliminated.
            Q_PROPERTY( int minKillVelocity READ minKillVelocity WRITE setMinKillVelocity )

            // Which Layers the particle will collide against.
            Q_PROPERTY( QString collidesWith READ collidesWith WRITE setCollidesWith )

            // If enabled, every particle sends out a collision message that you can catch through scripting.
            Q_PROPERTY( bool sendCollisionMessage READ sendCollisionMessage WRITE setSendCollisionMessage )

        public:
            Q_INVOKABLE ParticleColliderComponent( QObject* parent = 0 );
            ParticleColliderComponent( const ParticleColliderComponent& other );
            ~ParticleColliderComponent();

            QString category() const;

            void initialize();
            void start();
            void update( int elapsedMilliseconds );
            void draw( int timeLapse = 0 );
            void cleanup();

            float bounceFactor() const;
            int collisionEnergyLoss() const;
            int minKillVelocity() const;
            QString collidesWith() const;
            bool sendCollisionMessage() const;

        public slots:
            void setBounceFactor( float bounceFactor );
            void setCollisionEnergyLoss( int collisionEnergyLoss );
            void setMinKillVelocity( int minKillVelocity );
            void setCollidesWith( const QString& collidesWith );
            void setSendCollisionMessage( bool sendCollisionMessage );

        private:
            class Private;
            Private* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::ParticleColliderComponent* )

#endif // GLUON_ENGINE_PARTICLECOLLIDERCOMPONENT_H
