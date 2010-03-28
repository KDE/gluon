/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
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

#include "gridmesh.h"
namespace GluonGraphics
{
    GridMesh::GridMesh(QObject* parent)
            : Mesh(parent)
    {
        setGrid(QSizeF(5, 5), 1);
    }
    GridMesh::GridMesh(QSizeF size, float tile, QObject* parent)
            : Mesh(parent)
    {
        setGrid(size, tile);
    }


    void GridMesh::setGrid(QSizeF size, float tile)
    {
        m_tile = tile;
        m_size = size;
        clear();
        setGLMode(GL_TRIANGLE_STRIP);
        for (float j = 0; j <= m_size.height();j += m_tile)
        {
            for (float i = 0; i <= m_size.width(); i += m_tile)
            {
                addVertex(Vertex(i, j, Qt::white, QVector2D(i / m_size.width(), j / m_size.height())));
                addVertex(Vertex(i, j + m_tile, Qt::white, QVector2D(i / m_size.width(), (j + m_tile) / m_size.height())));
            }
        }

    }

}
