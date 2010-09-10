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

#ifndef GLUONGRAPHICS_MESH_H
#define GLUONGRAPHICS_MESH_H

#include "gluon_graphics_export.h"

#include <QtCore/QObject>

class QMatrix4x4;
namespace GluonGraphics
{
    class MaterialInstance;
    /**
     * \brief A collection of vertices that combine to an object.
     *
     * A mesh contains all data to correctly render an object to
     * the screen.
     */
    class GLUON_GRAPHICS_EXPORT Mesh : public QObject
    {
        Q_OBJECT
        public:
            Mesh(QObject * parent = 0);
            virtual ~Mesh();

            /**
             * Load the data for this mesh.
             *
             * \param filename The name of the file to load.
             */
            virtual void load(const QString& filename);

            /**
             * Render this mesh to the screen.
             *
             * \param modelViewProj The model-view-projection matrix
             * to use when rendering this mesh.
             */
            virtual void render(const QMatrix4x4& modelViewProj);

            void setMaterial(MaterialInstance * material);

        private:
            class MeshPrivate;
            MeshPrivate * const d;

    };
}//namespace

#endif // GLUONGRAPHICS_MESH_H
