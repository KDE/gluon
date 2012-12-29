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

            void render();

            Camera* activeCamera() const;
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
