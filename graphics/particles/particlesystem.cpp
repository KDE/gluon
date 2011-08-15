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


#include "particlesystem.h"
#include "particleemitter.h"

REGISTER_OBJECTTYPE(GluonGraphics, ParticleSystem)

using namespace GluonGraphics;

class ParticleSystem::Private
{
    public:
        Private() { }
        ~Private() { }

        QHash< QString, ParticleEmitter* > emitters;
};

ParticleSystem::ParticleSystem(QObject* parent)
    : GluonCore::GluonObject(parent), d(new Private)
{

}

ParticleSystem::~ParticleSystem()
{

}

ParticleEmitter* ParticleSystem::createEmitter(const QString& name)
{
    return 0;
}

bool ParticleSystem::addEmitter(const QString& name, ParticleEmitter* emitter)
{
    return false;
}

ParticleEmitter* ParticleSystem::emitter(const QString& name)
{
    return 0;
}

void ParticleSystem::destroyEmitter(const QString& name)
{

}

void ParticleSystem::removeEmitter(const QString& name)
{

}

void ParticleSystem::update()
{
    QHash< QString, ParticleEmitter* >::const_iterator itr;
    for(itr = d->emitters.begin(); itr != d->emitters.end(); ++itr)
    {
        itr.value()->update();
    }
}

#include "particlesystem.moc"

