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
namespace GluonGraphics
{
    DiscMesh::DiscMesh(QObject * parent)
            : Mesh(parent)
    {

        setDisc(1, 10);
    }
    DiscMesh::DiscMesh(float radius, unsigned int nbPoints, QObject *parent)
            : Mesh(parent)
    {

        setDisc(radius, nbPoints);
    }

    void DiscMesh::setDisc(float radius, unsigned int nbPoints)
    {

        clear();
        setGLMode(GL_POLYGON);
        if (nbPoints < 3)
        {
            return;
        }

        float step = M_PI * 2 / (float)nbPoints;

        for (float i = 0; i < M_PI*2; i += step)
        {
            float x = cos(i) ;
            float y = sin(i)  ;
            addVertex(Vertex(x*radius, y*radius, Qt::white, QVector2D(x, y)));
        }
    }
}
