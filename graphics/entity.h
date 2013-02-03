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

#include "gluon_graphics_export.h"

class QMatrix4x4;
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

            virtual World* world() const;

            /**
             * Retrieve the transformation matrix associated with
             * this item.
             *
             * \return The item's transformation matrix.
             */
            virtual QMatrix4x4 transform() const;

            /**
             * Retrieve the mesh currently used by this item.
             *
             * \return The item's mesh.
             */
            virtual Mesh* mesh() const;

            virtual bool hasMesh() const;

            /**
             * Retrieve the material instance used by this item.
             *
             * \see GluonGraphics::MaterialInstance
             *
             * \return The material instance used by this item.
             */
            virtual MaterialInstance* materialInstance() const;

            virtual bool hasMaterialInstance() const;

            virtual bool isVisible() const;

        public Q_SLOTS:
            virtual void setWorld( World* world );

            /**
             * Render the item to screen using the material set.
             */
            virtual void render();

            /**
             * Set the transformation used for this item.
             *
             * \param transform The new transformation to use.
             */
            virtual void setTransform( const QMatrix4x4 transform );

            /**
             * Set the mesh used by this item.
             *
             * \param mesh The mesh to use.
             */
            virtual void setMesh( Mesh* mesh );

            /**
             * Set the material instance that needs to be used by
             * this item.
             *
             * \param material The material instance to use.
             */
            virtual void setMaterialInstance( MaterialInstance* material );

            virtual void setVisible( bool visible );

        private:
            class Private;
            Private* const d;
    };

}

Q_DECLARE_METATYPE( GluonGraphics::Entity* );

#endif // GLUONGRAPHICS_ITEM_H
