/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "gluon_graphics_export.h"

#include <QtCore/QObject>

class QMatrix4x4;
namespace GluonGraphics
{

class MaterialInstance;

    class Mesh;

    /**
     * \brief An object in 3D-space.
     *
     * The item class describes an object in 3D-space. It
     * is essentially a transformation matrix and a mesh.
     * The Item object tells the associated mesh where it
     * should be rendered. This allows us to reuse a mesh
     * multiple times.
     */
    class GLUON_GRAPHICS_EXPORT Item : public QObject
    {
        Q_OBJECT
        public:
            Item(QObject * parent = 0);
            virtual ~Item();

            /**
             * Retrieve the transformation matrix associated with
             * this item.
             *
             * \return The item's transformation matrix.
             */
            QMatrix4x4 transform();

            /**
             * Retrieve the mesh currently used by this item.
             *
             * \return The item's mesh.
             */
            Mesh* mesh();

            /**
             * Retrieve the material instance used by this item.
             *
             * \see GluonGraphics::MaterialInstance
             *
             * \return The material instance used by this item.
             */
            MaterialInstance* materialInstance();

        public Q_SLOTS:
            /**
             * Render the item to screen.
             */
            virtual void render();

            /**
             * Set the transformation used for this item.
             *
             * \param transform The new transformation to use.
             */
            void setTransform(const QMatrix4x4 transform);

            /**
             * Set the mesh used by this item.
             *
             * \param mesh The mesh to use.
             */
            void setMesh(Mesh* mesh);

            /**
             * Set the material instance that needs to be used by
             * this item.
             *
             * \param material The material instance to use.
             */
            void setMaterialInstance(MaterialInstance * material);

        private:
            class ItemPrivate;
            ItemPrivate * const d;
    };

}
#endif // GLUONGRAPHICS_ITEM_H
