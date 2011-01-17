/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Giulio Camuffo <giuliocamuffo@gmail.com>
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

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <QtCore/QObject>
#include "glheaders.h"

namespace GluonGraphics
{
    class VertexAttribute;
    class MaterialInstance;

    /**
     * \brief A wrapper class around a GL vertex buffer object (VBO).
     *
     * A VertexBuffer takes any number of VertexAttribute and uses them
     * to create and draw a GL vertex buffer.
     */
    class VertexBuffer : public QObject
    {
        Q_OBJECT
        public:
            enum RenderMode
            {
                RM_POINTS,
                RM_LINES,
                RM_LINE_LOOP,
                RM_LINE_STRIP,
                RM_TRIANGLES,
                RM_TRIANGLE_STRIP,
                RM_TRIANGLE_FAN,
            };

            VertexBuffer( QObject* parent = 0 );
            ~VertexBuffer();

            /**
             * Add a vertex attribute to the list of attributes that will
             * be used by initialize().
             *
             * \param attribute The attribute to be added.
             **/
            void addAttribute( const VertexAttribute& attribute );

            /**
             * Sets the vertex indices to be used when rendering.
             *
             * \param indices The indices array.
             **/
            void setIndices( const QVector<uint>& indices );

            /**
             * Create an OpenGL buffer and store the previously added attributes.
             *
             * \see isInitialized
             */
            void initialize();

            /**
             * Render the local OpenGL buffer.
             *
             * \param mode The OpenGL mode to use, for example GL_TRIAGLES.
             * \param material The material to get attribute locations from.
             */
            void render( RenderMode mode, GluonGraphics::MaterialInstance* material );

            /**
             * Returns true if initialize was called.
             *
             * \see initialize
             **/
            bool isInitialized() const;

        private:
            class VertexBufferPrivate;
            VertexBufferPrivate* const d;
    };
};

#endif
