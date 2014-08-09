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

#ifndef GLUON_ENGINE_SPHERECOLLISIONCOMPONENT_H
#define GLUON_ENGINE_SPHERECOLLISIONCOMPONENT_H

#include <engine/component.h>

namespace GluonEngine
{
    /**
     * This class handles simple sphere-based collision.
     * Spherical collision is the most simple algorithm for collision
     * detection and thus also the fastest.
     *
     * Collision components use simple integer-based grouping to
     * exclude/include other components to collide with.
     */
    class SphereCollisionComponent : public Component
    {
            Q_OBJECT
            Q_INTERFACES( GluonEngine::Component )
            GLUON_OBJECT( GluonEngine::SphereCollisionComponent )
            GLUON_COMPONENT_PLUGIN(metadata.json)

            Q_PROPERTY( int collisionGroup READ collisionGroup WRITE setCollisionGroup )
            Q_PROPERTY( int targetGroup READ targetGroup WRITE setTargetGroup )
            Q_PROPERTY( float radius READ radius WRITE setRadius )

        public:
            /**
             * Constructor.
             */
            Q_INVOKABLE SphereCollisionComponent( QObject* parent = 0 );

            /**
             * Destructor.
             */
            virtual ~SphereCollisionComponent();

            virtual QString category() const;

            virtual void start();

            virtual void stop();

            /**
             * Update method.
             * This method does the actual collision calculation.
             *
             * @see Component::update();
             */
            virtual void update( int elapsedMilliseconds );

            /**
             * The collision group this object belongs to.
             */
            int collisionGroup() const;

            /**
             * The radius of this object.
             */
            float radius() const;

            float radiusSquared() const;

            int targetGroup() const;

            /**
             * Is this object colliding with something?
             */
            Q_INVOKABLE bool isColliding() const;

            /**
             * Retrieve the object this object is colliding with.
             *
             * @return The object this object is colliding with or 0
             * if there is no collision.
             */
            Q_INVOKABLE QObject* collidesWith() const;

        public Q_SLOTS:
            /**
             * Set the group this object belongs to.
             */
            void setCollisionGroup( int group );

            /**
             * Set the radius of this object.
             */
            void setRadius( float radius );

            void componentDestroyed( QObject* obj );

            void addComponent( SphereCollisionComponent* comp );

            void setTargetGroup( int group );

            /*Q_SIGNALS:
                 *
                 * Emitted when a collision occurs.
                 *
                 * @param comp The object this object collided with.
                 */
            //    void collides(SphereCollisionComponent* comp);

        private:
            class SphereCollisionComponentPrivate;
            SphereCollisionComponentPrivate* const d;
    };

}

Q_DECLARE_METATYPE( GluonEngine::SphereCollisionComponent* )

#endif // GLUON_ENGINE_SPHERECOLLISIONCOMPONENT_H
