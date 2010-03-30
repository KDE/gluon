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

#include "cubemesh.h"

namespace GluonGraphics
{
    CubeMesh::CubeMesh(QObject * parent)
            : Mesh(parent)
    {
        setCube(1, 1, 1);
    }
    CubeMesh::CubeMesh(float dimX, float dimY, float dimZ, QObject * parent)
            : Mesh(parent)
    {
        setCube(dimX, dimY, dimZ);
    }

    CubeMesh::CubeMesh(float dim, QObject * parent)
            : Mesh(parent)
    {
        setCube(dim, dim, dim);
    }

    void CubeMesh::setCube(float dimX, float dimY, float dimZ)
    {
        m_dimX = dimX;
        m_dimY = dimY;
        m_dimZ = dimZ;

        clear();
        setGLMode(GL_QUADS);
        addVertex(Vertex(QVector3D(dimX, dimY, dimZ), Qt::red, QVector2D(1, 1)));
        addVertex(Vertex(QVector3D(dimX, dimY, -dimZ), Qt::red, QVector2D(1, 0)));
        addVertex(Vertex(QVector3D(-dimX, dimY, -dimZ), Qt::red, QVector2D(0, 0)));
        addVertex(Vertex(QVector3D(-dimX, dimY, dimZ), Qt::red, QVector2D(0, 1)));

        addVertex(Vertex(QVector3D(dimX, -dimY, dimZ), Qt::blue, QVector2D(0, 1)));
        addVertex(Vertex(QVector3D(dimX, -dimY, -dimZ), Qt::blue, QVector2D(0, 0)));
        addVertex(Vertex(QVector3D(dimX, dimY, -dimZ), Qt::blue, QVector2D(1, 0)));
        addVertex(Vertex(QVector3D(dimX, dimY, dimZ), Qt::blue, QVector2D(1, 1)));

        addVertex(Vertex(QVector3D(-dimX, -dimY, dimZ), Qt::green, QVector2D(0, 1)));
        addVertex(Vertex(QVector3D(-dimX, -dimY, -dimZ), Qt::green, QVector2D(0, 0)));
        addVertex(Vertex(QVector3D(dimX, -dimY, -dimZ), Qt::green, QVector2D(1, 0)));
        addVertex(Vertex(QVector3D(dimX, -dimY, dimZ), Qt::green, QVector2D(1, 1)));

        addVertex(Vertex(QVector3D(-dimX, dimY, dimZ), Qt::yellow, QVector2D(1, 1)));
        addVertex(Vertex(QVector3D(-dimX, dimY, -dimZ), Qt::yellow, QVector2D(1, 0)));
        addVertex(Vertex(QVector3D(-dimX, -dimY, -dimZ), Qt::yellow, QVector2D(0, 0)));
        addVertex(Vertex(QVector3D(-dimX, -dimY, dimZ), Qt::yellow, QVector2D(0, 1)));

        addVertex(Vertex(QVector3D(dimX, dimY, -dimZ), Qt::white, QVector2D(1, 1)));
        addVertex(Vertex(QVector3D(dimX, -dimY, -dimZ), Qt::white, QVector2D(1, 0)));
        addVertex(Vertex(QVector3D(-dimX, -dimY, -dimZ), Qt::white, QVector2D(0, 0)));
        addVertex(Vertex(QVector3D(-dimX, dimY, -dimZ), Qt::white, QVector2D(0, 1)));

        addVertex(Vertex(QVector3D(dimX, -dimY, dimZ), Qt::cyan, QVector2D(1, 0)));
        addVertex(Vertex(QVector3D(dimX, dimY, dimZ), Qt::cyan, QVector2D(1, 1)));
        addVertex(Vertex(QVector3D(-dimX, dimY, dimZ), Qt::cyan, QVector2D(0, 1)));
        addVertex(Vertex(QVector3D(-dimX, -dimY, dimZ), Qt::cyan, QVector2D(0, 0)));



    }
}
