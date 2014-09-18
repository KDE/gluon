/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUONGRAPHICS_WORLD_H
#define GLUONGRAPHICS_WORLD_H

#include <QtCore/QObject>

#include "gluon_graphics_export.h"

namespace GluonGraphics
{
    class Entity;
    class Sprite;
    class Camera;

    /**
     * Container class for entities in 3D space.
     *
     * The world is used as a container for managing entities in 3D space. It maintains a list
     * of all entities contained within the world and will be used by Camera to do rendering.
     *
     * The world class will sort entities based on their Z depth using a stable sorting algorithm
     * to reduce Z fighting.
     *
     * \todo Implement frustum culling and other things to improve render speed.
     */
    class GLUON_GRAPHICS_EXPORT World : public QObject
    {
            Q_OBJECT
        public:
            explicit World( QObject* parent = 0 );
            virtual ~World();


            template < typename T > T* createEntity();
            void addEntity( Entity* entity );
            Entity* entity( int index ) const;
            int entityIndex( Entity* entity ) const;
            void destroyEntity( int index );
            void destroyEntity( Entity* entity );

            /**
             * Render the contents of this world.
             */
            void render();

            /**
             * \return The current active camera.
             */
            Camera* activeCamera() const;
            /**
             * Set the active camera.
             *
             * The active camera will be used during rendering to determine the view and projection
             * matrices. To render from a different camera, call setActiveCamera( camera ) and after
             * that render();
             *
             * \param cam The camera to set as the active camera.
             */
            void setActiveCamera( Camera* cam );

        private:
            class Private;
            Private* const d;
    };

    template < typename T > T* World::createEntity()
    {
        T* newEntity = new T( this );
        addEntity( newEntity );
        return newEntity;
    }
}

#endif // GLUONGRAPHICS_WORLD_H
