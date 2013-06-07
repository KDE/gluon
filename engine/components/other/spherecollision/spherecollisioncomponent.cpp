/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "spherecollisioncomponent.h"

#include <core/debughelper.h>
#include <engine/gameobject.h>
#include <engine/game.h>
#include <engine/scene.h>

REGISTER_OBJECTTYPE( GluonEngine, SphereCollisionComponent )

using namespace GluonEngine;

class SphereCollisionComponent::SphereCollisionComponentPrivate
{
    public:
        SphereCollisionComponentPrivate() :
            collisionGroup( 0 ),
            targetGroup( 0 ),
            radius( 1.0f ),
            collides( 0 )
        {
        }

        int collisionGroup;
        int targetGroup;
        float radius;
        float radiusSquared;
        GameObject* collides;

        int componentType;
        const char* typeName;

        QVector<Component*> collisionComponents;
};

SphereCollisionComponent::SphereCollisionComponent( QObject* parent )
    : Component( parent )
    , d( new SphereCollisionComponentPrivate )
{
    d->componentType = qMetaTypeId<GluonEngine::SphereCollisionComponent*>();
}

SphereCollisionComponent::~SphereCollisionComponent()
{
    delete d;
}

QString SphereCollisionComponent::category() const
{
    return QString( "Physics" );
}

void SphereCollisionComponent::start()
{
    d->collisionComponents = gameObject()->scene()->sceneContents()->findComponentsInChildrenByType( d->componentType ).toVector();

    int counter = 0;
    foreach( Component * component, d->collisionComponents )
    {
        if( component->enabled() && component->gameObject()->enabled() )
        {
            connect( component, SIGNAL(destroyed(QObject*)), SLOT(componentDestroyed(QObject*)) );
            static_cast<SphereCollisionComponent*>( component )->addComponent( this );
        }
        else
        {
            d->collisionComponents.replace( counter, 0 );
        }
        counter++;
    }
}

void SphereCollisionComponent::update( int /* elapsedMilliseconds */ )
{
    d->collides = 0;

    //Our position
    Eigen::Vector3f position = gameObject()->position();
    //Eliminate the Z-axis
    position.z() = 0;
    //Our radius, squared
    float radius = d->radiusSquared;

    //Walk through the list
    const int componentCount = d->collisionComponents.count();
    Component** data = d->collisionComponents.data();
    for( int i = 0; i < componentCount; ++i )
    {
        SphereCollisionComponent* sphere = qobject_cast< SphereCollisionComponent* >( data[i] );
        if( sphere && sphere != this )
        {
            //See if we are in the same group
            if( sphere->collisionGroup() == d->targetGroup )
            {
                //Get the object's position
                Eigen::Vector3f otherPosition = sphere->gameObject()->position();
                //Eliminate the Z axis
                position.z() = 0;

                //Get the object's radius
                float otherRadius = sphere->radiusSquared();

                //Calculate the distance between our position and theirs
                //Note that this is the squared distance to avoid a costly squareroot op
                float dist = ( otherPosition - position ).squaredNorm();

                //If the distance between the two positions is smaller then the radius, we
                //have a collision.
                if( dist < ( otherRadius + radius ) )
                {
                    d->collides = sphere->gameObject();
                }
            }
        }
    }
}

void SphereCollisionComponent::stop()
{
}

int SphereCollisionComponent::collisionGroup() const
{
    return d->collisionGroup;
}

float SphereCollisionComponent::radius() const
{
    return d->radius;
}

float SphereCollisionComponent::radiusSquared() const
{
    return d->radiusSquared;
}

bool SphereCollisionComponent::isColliding() const
{
    return d->collides != 0;
}

QObject* SphereCollisionComponent::collidesWith() const
{
    return d->collides;
}

void SphereCollisionComponent::setCollisionGroup( int group )
{
    d->collisionGroup = group;
}

int SphereCollisionComponent::targetGroup() const
{
    return d->targetGroup;
}

void SphereCollisionComponent::setTargetGroup( int group )
{
    d->targetGroup = group;
}

void SphereCollisionComponent::setRadius( float radius )
{
    d->radius = radius;
    d->radiusSquared = radius * radius;
}

void SphereCollisionComponent::componentDestroyed( QObject* obj )
{
    if( !obj )
        return;

    Component* comp = static_cast<Component*>( obj );
    if( d->collisionComponents.contains( comp ) )
        d->collisionComponents.remove( d->collisionComponents.indexOf( comp ) );
}

void SphereCollisionComponent::addComponent( SphereCollisionComponent* comp )
{
    if( comp )
    {
        if( !d->collisionComponents.contains( comp ) )
        {
            d->collisionComponents.append( comp );
            connect( comp, SIGNAL(destroyed(QObject*)), this, SLOT(componentDestroyed(QObject*)) );
        }
    }
}

Q_EXPORT_PLUGIN2( gluon_component_spherecollision, GluonEngine::SphereCollisionComponent )

 
