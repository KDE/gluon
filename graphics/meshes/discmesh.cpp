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

#include "discmesh.h"
#include <cmath>
#include <QtGui/QVector3D>
namespace GluonGraphics
{
    DiscMesh::DiscMesh(QObject * parent)
            : Mesh(parent)
    {
    }
    DiscMesh::DiscMesh(QVector3D position, float radius, int nbPoints, QColor color, QObject* parent)
            : Mesh(parent)
    {

        setDisc(position, radius, nbPoints, color);
    }

    void DiscMesh::setDisc(QVector3D position, float radius, int nbPoints, QColor color)
    {
        clear();
        setGLMode(GL_POLYGON);
        if (nbPoints < 3)
        {
            nbPoints = 3;
        }

        float step = M_PI * 2 / (float)nbPoints;

        for (float i = 0; i < M_PI*2; i += step)
        {
            float x = cos(i) ;
            float y = sin(i)  ;
            addVertex(Vertex(x*radius, y*radius, color, QVector2D(x, y)));
        }
    }
}
