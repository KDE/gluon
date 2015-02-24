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

#ifndef GLUONGRAPHICS_MESHDATA_H
#define GLUONGRAPHICS_MESHDATA_H

#include <QVariant>
#include <QVector>

#include "gluon_graphics_export.h"

namespace GluonGraphics
{
    class Shader;
    class Buffer;

    /**
     * A class abstracting the concept of a "mesh".
     *
     * A mesh is a collection of vertexes consisting of a positions, uv coordinates and other attributes and
     * a list of indexes connecting the vertexes to each other to make faces. This class provides an abstract
     * interface for backends to implement mesh handling.
     *
     * To use this class to provide a mesh, use setAttribute to add position data and setIndices to add the
     * index data. If you need additional per-vertex data, use setAttribute to add them. The interface was
     * designed to make no major assumptions of what kind of data can be provided as attributes, similar to
     * how modern graphics cards make no such assumptions. The attribute name should be used in your shader
     * to bind the actual attribute. For example, if you set an attribute named "position" of type Vector3f,
     * your shader should use a line like <code>attribute vec3 position;</code> to access the attribute.
     *
     * \note To prevent excessive resizing of the internal buffer objects used for most implementations of
     * this class, the method setPrimitiveCount(int, int, int) should be used to give a hint to the amount
     * of vertices that will be used by the mesh.
     */
    class GLUON_GRAPHICS_EXPORT MeshData
    {
        public:
            /**
             * The type of primitive this mesh represents.
             */
            enum PrimitiveType
            {
                PointPrimitive, ///< Each vertex is a point, no edges are drawn between them.
                LinePrimitive, ///< Each vertex is a point and they are connected by lines. No fill of the polygon happens.
                TrianglePrimitive, ///< Each vertex is a point and they are connected by edges making up a solid triangle.
                TriangleFanPrimitive, ///< The first vertex is a center point in a fan of triangles determined by the other vertices.
                TriangleStripPrimitive, ///< Each set of three vertices forms a triangle, starting at index 0 and incrementing by 1.
            };

            /**
             * The type of vertex attribute to set for this mesh.
             */
            enum AttributeType
            {
                CharAttribute,
                IntAttribute,
                UIntAttribute,
                FloatAttribute,
                DoubleAttribute,
                Vector2fAttribute,
                Vector3fAttribute,
                Vector4fAttribute,
            };

            MeshData();
            virtual ~MeshData();

            /**
             * Set a vertex attribute for this mesh.
             *
             * The specified attribute will be added to the internal representation for this mesh and become
             * available to the shader. Note that this may be delayed until the next frame if rendering is
             * currently happening. In addition, this may cause buffer resizes so can be potentially slow.
             *
             * \param name The name of the attribute to set.
             * \param type The type of attribute to set.
             * \param data A vector containing the data to be used for this attribute.
             */
            template < typename T >
            void setAttribute( const QString& name, AttributeType type, QVector< T > data ); //Note: Explicit use of copy-by-value for QVector, do not change!
            /**
             * Set the indices for this mesh.
             *
             * The precise interpretation of the data depends on the primitive type and the backend used.
             *
             * \param indices A vector containing the data to be used for the indices.
             */
            virtual void setIndices( QVector< uint > indices ) = 0; //Note: Explicit use of copy-by-value for QVector, do not change!

            /**
             * \return The primitive type this mesh uses to render.
             */
            PrimitiveType primitiveType() const;
            /**
             * Set the primitive type this mesh should use to render.
             *
             * \note It depends on the backend whether it is possible to switch primitive type without
             * needing to recreate the internal representation of the mesh.
             */
            virtual void setPrimitiveType( PrimitiveType type );

            /**
             * \return The amount of primitive this mesh consists of.
             */
            int primitiveCount() const;
            /**
             * Provide a hint to the backend about how much data should be pre-allocated for this mesh.
             *
             * \param count The amount of primitives that will be used by this mesh.
             * \param vertexSize The total size of the vertex data for this mesh.
             * \param indexSize The total size of the index data for this mesh.
             */
            virtual void setPrimitiveCount( int count, int vertexSize, int indexSize ) = 0;
            virtual void setPrimitiveCount( int count );

            /**
             * Render this mesh to screen using shader.
             */
            virtual void render( Shader* shader ) = 0;

        protected:
            virtual void setAttribute( const QString& name, AttributeType type, void* data, int size ) = 0;

        private:
            class Private;
            Private* const d;
    };

    template < typename T >
    void MeshData::setAttribute( const QString& name, MeshData::AttributeType type, QVector< T > data )
    {
        setAttribute( name, type, reinterpret_cast< void* >( data.data() ), sizeof( T ) * data.size() );
    }
}

#endif // GLUONGRAPHICS_MESHDATA_H
