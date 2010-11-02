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

#include "gameobject.h"
#include "game.h"
#include "scene.h"

#include <core/debughelper.h>

REGISTER_OBJECTTYPE(GluonEngine, SphereCollisionComponent)

using namespace GluonEngine;

class SphereCollisionComponent::SphereCollisionComponentPrivate
{
    public:
        SphereCollisionComponentPrivate() { collisionGroup = 0; radius = 1.0f; collides = 0; }

        int collisionGroup;
        float radius;
        GameObject *collides;
};

SphereCollisionComponent::SphereCollisionComponent(QObject *parent)
    : Component(parent)
    , d(new SphereCollisionComponentPrivate)
{

}

SphereCollisionComponent::~SphereCollisionComponent()
{
    delete d;
}

QString SphereCollisionComponent::category() const
{
    return QString("Physics");
}

void SphereCollisionComponent::update(int elapsedMilliseconds)
{
    Q_UNUSED(elapsedMilliseconds)

    d->collides = 0;

    //Retrieve a list of all the other CollisionComponents
    QList<Component *> collisionComponents = Game::instance()->currentScene()->sceneContents()->findComponentsInChildrenByType("GluonEngine::SphereCollisionComponent");

    //Our position
    QVector3D position = gameObject()->position();
    //Eliminate the Z-axis
    position.setZ(0);
    //Our radius, squared
    float radius = d->radius * d->radius;

    //Walk through the list
    foreach (Component *component, collisionComponents) {
        //Get the correct type
        SphereCollisionComponent *object = qobject_cast<SphereCollisionComponent*>(component);

        if (object && object != this) {
            //See if we are in the same group
            if (object->collisionGroup() == d->collisionGroup) {
                //Get the object's position
                QVector3D otherPosition = object->gameObject()->position();
                //Eliminate the Z axis
                position.setZ(0);

                //Get the object's radius
                float otherRadius = object->radius();

                //Calculate the distance between our position and theirs
                //Note that this is the squared distance to avoid a costly squareroot op
                float dist = (otherPosition - position).lengthSquared();

                //If the distance between the two positions is smaller then the radius, we
                //have a collision.
                if (dist < (otherRadius + radius)) {
                    d->collides = object->gameObject();
                }
            }
        }
    }
}

int SphereCollisionComponent::collisionGroup() const
{
    return d->collisionGroup;
}

float SphereCollisionComponent::radius() const
{
    return d->radius;
}

bool SphereCollisionComponent::isColliding() const
{
    return d->collides != 0;
}

QObject* SphereCollisionComponent::collidesWith() const
{
    return d->collides;
}

void SphereCollisionComponent::setCollisionGroup(int group)
{
    d->collisionGroup = group;
}

void SphereCollisionComponent::setRadius(float radius)
{
    d->radius = radius;
}

Q_EXPORT_PLUGIN2(gluon_component_spherecollision, GluonEngine::SphereCollisionComponent)

#include "spherecollisioncomponent.moc"
