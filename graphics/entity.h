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

#ifndef GLUONGRAPHICS_ITEM_H
#define GLUONGRAPHICS_ITEM_H

#include <core/gluonobject.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "gluon_graphics_export.h"

namespace GluonGraphics
{
    class World;
    class MaterialInstance;
    class Mesh;

    /**
     * \brief An object in 3D-space.
     *
     * The Entity class describes an object in 3D-space. It
     * is essentially a transformation matrix and a mesh.
     * The Entity object tells the associated mesh where it
     * should be rendered. This allows us to reuse a mesh
     * multiple times.
     */
    class GLUON_GRAPHICS_EXPORT Entity : public GluonCore::GluonObject
    {
            Q_OBJECT
            GLUON_OBJECT( Entity )

        public:
            Entity( QObject* parent = 0 );
            virtual ~Entity();

            /**
             * \return The world this entity is contained in.
             */
            virtual World* world() const;

            /**
             * Retrieve the transformation matrix associated with
             * this entity.
             *
             * \return The entity's transformation matrix.
             */
            virtual Eigen::Affine3f transform() const;

            /**
             * Retrieve the mesh currently used by this entity.
             *
             * \return The entity's mesh.
             */
            virtual Mesh* mesh() const;

            /**
             * \return True if there is a mesh attached to this entity, false if not.
             */
            virtual bool hasMesh() const;

            /**
             * Retrieve the material instance used by this entity.
             *
             * \see GluonGraphics::MaterialInstance
             *
             * \return The material instance used by this entity.
             */
            virtual MaterialInstance* materialInstance() const;

            /**
             * \return True if there is a material instance attached to this entity, false if not.
             */
            virtual bool hasMaterialInstance() const;

            /**
             * \return True if this entity should be rendered (visible), false if not.
             */
            virtual bool isVisible() const;

        public Q_SLOTS:
            /**
             * Set the world containing this entity.
             *
             * The world is primarily used for sorting and rendering all entities.
             *
             * \sa World
             *
             * \param world The world this entity should be contained in.
             */
            virtual void setWorld( World* world );

            /**
             * Render the entity to screen.
             *
             * This will render the entity to screen using the given mesh and material
             * instance. If neither is assigned, this method will do nothing.
             */
            virtual void render();

            /**
             * Set the transformation used to render this entity.
             *
             * \param transform The new transformation to use.
             */
            virtual void setTransform( const Eigen::Affine3f& transform );

            /**
             * Set the mesh that should be used to render this entity.
             *
             * \param mesh The mesh to use.
             */
            virtual void setMesh( Mesh* mesh );

            /**
             * Set the material instance that should be used to render
             * this entity.
             *
             * \param material The material instance to use.
             */
            virtual void setMaterialInstance( MaterialInstance* material );

            /**
             * Set whether this entity should be rendered at all.
             *
             * \param visible True if it should be rendered, false if not.
             */
            virtual void setVisible( bool visible );

        private:
            class Private;
            Private* const d;
    };

}

Q_DECLARE_METATYPE( GluonGraphics::Entity* );

#endif // GLUONGRAPHICS_ITEM_H
