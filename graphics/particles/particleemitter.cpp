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


#include "particleemitter.h"
#include "particle.h"
#include "particlerenderer.h"
#include <QMatrix4x4>
#include "particleaffector.h"

REGISTER_OBJECTTYPE( GluonGraphics, ParticleEmitter )

using namespace GluonGraphics;

class ParticleEmitter::Private
{
    public:
        Private() { }

        QList< Particle* > particles;
        QList< ParticleAffector* > affectors;
        ParticleRenderer* renderer;

        float spawnRate;
        bool enabled;
        bool renderable;
        bool attach;

        int msecElapsed;
        int msecPerSpawn;
};

ParticleEmitter::ParticleEmitter(QObject* parent)
    : Item( parent ), d( new Private )
{

}

ParticleEmitter::~ParticleEmitter()
{
    qDeleteAll(d->particles);
}

float ParticleEmitter::spawnRate() const
{
    return d->spawnRate;
}

void ParticleEmitter::setSpawnRate(float rate)
{
    d->spawnRate = rate;
    Q_ASSERT(rate != 0)
    d->msecPerSpawn = 1000/rate;
}

bool ParticleEmitter::isEnabled() const
{
    return d->enabled;
}

void ParticleEmitter::setEnabled(bool enable)
{
    d->enabled = enable;
}

bool ParticleEmitter::isRenderable() const
{
    return d->renderable;
}

void ParticleEmitter::setRenderable(bool render)
{
    d->renderable = render;
}

bool ParticleEmitter::attachParticles() const
{
    return d->attach;
}

void ParticleEmitter::setAttachParticles(bool attach)
{
    d->attach = attach;
}

void ParticleEmitter::render()
{
    if( !d->renderable )
        return;

    if( d->attach )
    {
        d->renderer->render( d->particles, transform() );
    }
    else
    {
        d->renderer->render( d->particles );
    }
}

void ParticleEmitter::update( int time )
{
    if( !d->enabled )
        return;

    d->msecElapsed += time;
    if( d->msecElapsed >= d->msecPerSpawn )
    {
        d->particles.append( emitParticle() );
        d->msecElapsed = 0;
    }

    const int affectorCount = d->affectors.count();
    const int particleCount = d->particles.count();
    Particle* particle;
    for( int i = 0; i < particleCount; ++i )
    {
        particle = d->particles.at( i );
        particle->age += time;

        //TODO: Potential improvement here: Use template metaprogramming to unroll loop.
        for( int j = 0; j < affectorCount; ++j )
        {
            d->affectors.at( j )->affectParticle( particle, time );
        }
    }
}

#include "particleemitter.moc"
