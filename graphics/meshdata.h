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

namespace GluonGraphics
{
    class Shader;
    class Buffer;

    class MeshData
    {
        public:
            enum PrimitiveType
            {
                PointType,
                LineType,
                TriangleType,
                TriangleFanType,
                TriangleStripType,
            };

            MeshData();
            virtual ~MeshData();

            template < typename T >
            void setAttribute( const QString& name, QVariant::Type type, QVector< T > data ); //Note: Explicit use of copy-by-value for QVector, do not change!
            virtual void setIndices( QVector< uint > indices ) = 0; //Note: Explicit use of copy-by-value for QVector, do not change!

            PrimitiveType primitiveType() const;
            virtual void setPrimitiveType( PrimitiveType type );

            int primitiveCount() const;
            virtual void setPrimitiveCount( int count );
            virtual void setPrimitiveCount( int count, int vertexSize, int indexSize ) = 0;

            virtual void render( Shader* shader ) = 0;

        protected:
            virtual void setAttribute( const QString& name, QVariant::Type type, void* data, int size ) = 0;

        private:
            class Private;
            Private* const d;
    };

    template < typename T >
    void MeshData::setAttribute( const QString& name, QVariant::Type type, QVector< T > data )
    {
        setAttribute( name, type, reinterpret_cast< void* >( data.data() ), sizeof( T ) * data.size() );
    }
}

#endif // GLUONGRAPHICS_MESHDATA_H
