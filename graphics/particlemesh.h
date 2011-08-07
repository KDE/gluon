/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#ifndef GLUONGRAPHICS_PARTICLEMESH_H
#define GLUONGRAPHICS_PARTICLEMESH_H

#include "abstractmesh.h"
#include "gluon_graphics_export.h"

namespace GluonGraphics
{
    /**
    * \brief A point particle cloud mesh.
    *
    * This class implements a cloud of points that uses the
    * dynamic mode to update the mesh.
    */
    class GLUON_GRAPHICS_EXPORT ParticleMesh : public GluonGraphics::AbstractMesh
    {
        public:
            ParticleMesh( QObject* parent );
            virtual ~ParticleMesh();

            virtual void initialize();
            virtual void update();
            virtual void render(GluonGraphics::MaterialInstance* material, GluonGraphics::VertexBuffer::RenderMode mode = VertexBuffer::RM_TRIANGLES);

        private:
            class Private;
            Private* const d;
    };

}

#endif // GLUONGRAPHICS_PARTICLEMESH_H
