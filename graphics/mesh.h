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
     * A mesh contains all the vertex data of an object. This
     * vertex data is used to render triangles on the screen.
     */
    class GLUON_GRAPHICS_EXPORT Mesh : public QObject
    {
            Q_OBJECT
        public:
            Mesh( QObject* parent = 0 );
            virtual ~Mesh();

            /**
             * Load the data for this mesh.
             *
             * \param filename The name of the file to load.
             */
            virtual void load( const QString& filename );

            /**
             * Has this mesh been loaded yet?
             */
            virtual bool isLoaded();

            /**
             * Render this mesh to the screen.
             *
             * \param material The material used to render the mesh. This
             * is only used to determine vertex attribute locations in the
             * program.
             * \param mode The GL mode used to render the mesh, like GL_TRIANGLES.
             */
            virtual void render( MaterialInstance* material, uint mode );

        protected:
            /**
             * Create an OpenGL buffer to store data and store the data
             * passed as arguments.
             *
             * \param vertices The vertex positions to store in the buffer.
             * \param colors The vertex colors to store in the buffer.
             * \param uvs The UV coordinate data to store in the buffer.
             */
            virtual void createBuffer( const QVector< float >& vertices, const QVector< float >& colors, const QVector< float >& uvs );

            /**
             * Render the local OpenGL buffer.
             *
             * \param mode The OpenGL mode to use, for example GL_TRIAGLES.
             * \param count The number of vertices to render.
             * \param material The material to get attribute locations from.
             */
            virtual void renderBuffer( uint mode, int count, GluonGraphics::MaterialInstance* material );

        private:
            class MeshPrivate;
            MeshPrivate* const d;

    };
}//namespace

#endif // GLUONGRAPHICS_MESH_H
