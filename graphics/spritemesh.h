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


#ifndef GLUONGRAPHICS_SPRITEMESH_H
#define GLUONGRAPHICS_SPRITEMESH_H

#include "abstractmesh.h"
#include "gluon_graphics_export.h"

namespace GluonGraphics
{
    /**
     * \brief A simple quad mesh for rendering sprites.
     *
     * This mesh provides a basic mesh for rendering
     * sprites. It defines the following attributes:
     *
     * - vertex
     * - color
     * - uv0
     */
    class GLUON_GRAPHICS_EXPORT SpriteMesh : public AbstractMesh
    {
            Q_OBJECT
        public:
            explicit SpriteMesh( QObject* parent = 0 );
            virtual ~SpriteMesh();

            virtual void initialize();
    };
}

#endif // GLUONGRAPHICS_SPRITEMESH_H
