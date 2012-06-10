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

#ifndef GLUONGRAPHICS_GLXMESHDATA_H
#define GLUONGRAPHICS_GLXMESHDATA_H

#include <QVector>

#include <meshdata.h>

namespace GluonGraphics
{
    class GLXMeshData : public GluonGraphics::MeshData
    {
        public:
            GLXMeshData();
            virtual ~GLXMeshData();

            virtual void render( Shader* shader );
            virtual void setIndices( QVector< uint > indices );
            virtual void setPrimitiveType( GluonGraphics::MeshData::PrimitiveType type );
            virtual void setPrimitiveCount(int count, int vertexSize, int indexSize);

        protected:
            virtual void setAttribute( const QString& name, QVariant::Type type, void* data, int size );

        private:
            class Private;
            Private * const d;
    };
}

#endif // GLUONGRAPHICS_GLXMESHDATA_H
