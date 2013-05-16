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


#include "forceaffector.h"
#include <QVector3D>

REGISTER_OBJECTTYPE( GluonGraphics, ForceAffector );

using namespace GluonGraphics;

class ForceAffector::Private
{
    public:
        Private() : randomness(0.f), transformSpace(World), continuous(false) { }

        QVector3D force;
        float randomness;
        TransformSpace transformSpace;
        bool continuous;

        bool forceApplied;
};

ForceAffector::ForceAffector( QObject* parent )
    : ParticleAffector( parent ), d( new Private )
{

}

ForceAffector::~ForceAffector()
{

}

void ForceAffector::affectParticle( Particle* particle, int time )
{

}

QVector3D ForceAffector::force() const
{
    return d->force;
}

void ForceAffector::setForce( const QVector3D& force )
{
    d->force = force;
}

float ForceAffector::randomness() const
{
    return d->randomness;
}

void ForceAffector::setRandomness( float random )
{
    d->randomness = random;
}

ForceAffector::TransformSpace ForceAffector::transformSpace() const
{
    return d->transformSpace;
}

void ForceAffector::setTransformSpace( ForceAffector::TransformSpace space )
{
    d->transformSpace = space;
}

bool ForceAffector::isContinuous() const
{
    return d->continuous;
}

void ForceAffector::setContinuous( bool continuous )
{
    d->continuous = continuous;
}
