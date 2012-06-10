/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010-2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUONGRAPHICS_ABSTRACTMESH_H
#define GLUONGRAPHICS_ABSTRACTMESH_H

#include <QObject>

#include "gluon_graphics_export.h"

namespace GluonGraphics
{
    class Buffer;
    class Shader;

    /**
     * \brief Abstract base class for different types of meshes.
     *
     * A mesh is a collection of data that combines to create an
     * object. This data consists of vertices, indexes and
     * possibly more. This data enables the mesh to be rendered
     * to screen.
     *
     * The exact interpretation of the data is handled by the
     * shader supplied by the material.
     *
     * If you want to create custom meshes, subclass this class
     * and reimplement at least load(). Load needs to create
     * a VertexBuffer and populate the buffer with data. If you
     * want to use dynamic meshes, you also need to reimplement
     * update(), which needs to adjust the data.
     */
    class GLUON_GRAPHICS_EXPORT Mesh : public QObject
    {
        Q_OBJECT
        public:
            explicit Mesh( QObject* parent = 0 );
            virtual ~Mesh();

            virtual void initialize() = 0;

            /**
             * Has this mesh been initialized yet?
             */
            virtual bool isInitialized() const;

            /**
             * Update the geometry of this mesh.
             *
             * The default implementation of this method does
             * nothing.
             */
            virtual void update();

            /**
             *
             */
            virtual void render( Shader* shader ) = 0;

        private:
            class Private;
            Private* const d;

    };
}

#endif // GLUONGRAPHICS_MESH_H
