/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
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

#ifndef DISCSECTIONMESH_H
#define DISCSECTIONMESH_H

#include "../gluon_graphics_export.h"
#include "../mesh.h"

class QVector3D;

namespace GluonGraphics
{
    class GLUON_GRAPHICS_EXPORT DiscSectionMesh: public Mesh
    {
        public:
            DiscSectionMesh(QObject * parent = 0);
            DiscSectionMesh(QVector3D position, float radius, uint nbPoints, float degrees, QColor color, QObject * parent = 0);
            void setDiscSection(QVector3D position, float radius, uint nbPoints, float degrees, QColor color);
    };
}
#endif