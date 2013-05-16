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
#include <core/gdlhandler.h>
#include <QFile>

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

bool ParticleSystem::load(const QUrl& path)
{
    QList< GluonCore::GluonObject > objects = GluonCore::GDLHandler::instance()->parseGDL( path, 0 );
    if( objects.size() == 0 )
        return false;

    ParticleSystem* system = qobject_cast< ParticleSystem* >( objects.at( 0 ) );
    if( !system )
        return false;

    unload();

    foreach( QObject* object, system->children() )
    {
        ParticleEmitter* emitter = qobject_cast< ParticleEmitter* >( object );
        if( emitter )
        {
            addEmitter( emitter );
            emitter->sanitize();
        }
    }

    qDeleteAll( objects );
}

bool ParticleSystem::save(const QUrl& path)
{
    QFile file( path.toLocalFile() );
    if( !file.open( QIODevice::WriteOnly ) )
        return false;

    QList< GluonCore::GluonObject* > list;
    list << this;
    QString parsed = GluonCore::GDLHandler::instance()->serializeGDL( list );

    if( !file.write( parsed.toUtf8() ) )
    {
        file.close();
        return false;
    }

    file.close();
}

void ParticleSystem::unload()
{
    d->emitters.clear();
    qDeleteAll( children() );h
}

ParticleEmitter* ParticleSystem::createEmitter( const QString& name, const QString& type )
{
    if( name.isEmpty() || type.isEmpty() )
        return 0;

    if( d->emitters.contains( name ) )
        return d->emitters.value( name );

    ParticleEmitter* emitter = qobject_cast< ParticleEmitter* >( GluonCore::GluonObjectFactory::instantiateObjectByName( type ) );

    if( !emitter )
        return 0;

    d->emitters.insert( name, emitter );
    emitter->setParent( this );
    emitter->setGameProject( gameProject() );

    return emitter;
}

bool ParticleSystem::addEmitter(const QString& name, ParticleEmitter* emitter)
{
    if( !emitter || name.isEmpty() || d->emitters.contains( name ) )
        return false;

    d->emitters.insert( name, emitter );
    emitter->setParent( this );
    emitter->setGameProject( gameProject() );

    return true;
}

ParticleEmitter* ParticleSystem::emitter(const QString& name)
{
    if( d->emitters.contains( name ) )
        return d->emitters.value( name );

    return 0;
}

void ParticleSystem::destroyEmitter(const QString& name)
{
    if( !d->emitters.contains( name ) )
        return;

    ParticleEmitter* emitter = d->emitters.value( name );
    d->emitters.remove( name );
    emitter->deleteLater();
}

void ParticleSystem::removeEmitter(const QString& name)
{
    if( !d->emitters.contains( name ) )
        return;

    d->emitters.remove( name );
}

void ParticleSystem::update( int time )
{
    QHash< QString, ParticleEmitter* >::const_iterator itr;
    for(itr = d->emitters.begin(); itr != d->emitters.end(); ++itr)
    {
        itr.value()->update( time );
    }
}

#include "particlesystem.moc"

