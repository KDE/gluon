/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#ifndef GLUONGRAPHICS_PARTICLEEMITTER_H
#define GLUONGRAPHICS_PARTICLEEMITTER_H

#include "item.h"

namespace GluonGraphics
{
    class Particle;
    class ParticleEmitter : public Item
    {
            Q_OBJECT
            GLUON_OBJECT( ParticleEmitter )

            Q_PROPERTY( float spawnRate READ spawnRate WRITE setSpawnRate )
            Q_PROPERTY( bool enabled READ isEnabled WRITE setEnabled )
            Q_PROPERTY( bool renderable READ isRenderable WRITE setRenderable )
            Q_PROPERTY( bool attachParticles READ attachParticles WRITE setAttachParticles )

        public:
            typedef QList< Particle* > ParticleList;

            Q_INVOKABLE ParticleEmitter( QObject* parent = 0 );
            virtual ~ParticleEmitter();

            float spawnRate() const;
            void setSpawnRate( float rate );

            bool isEnabled() const;
            void setEnabled( bool enable );

            bool isRenderable() const;
            void setRenderable( bool render );

            bool attachParticles() const;
            void setAttachParticles( bool attach );

            virtual void render();
            virtual void update( int time );

        protected:
            virtual Particle* emitParticle() = 0;

        private:
            class Private;
            const QScopedPointer<Private> d;
    };

}

Q_DECLARE_METATYPE( GluonGraphics::ParticleEmitter* )

#endif // GLUONGRAPHICS_PARTICLEEMITTER_H
