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
#include "discsectionmesh.h"

using namespace GluonGraphics;

#include <QtGui/QVector3D>
#include <cmath>

DiscSectionMesh::DiscSectionMesh(QObject* parent)
    : Mesh(parent)
{
}

DiscSectionMesh::DiscSectionMesh(QVector3D position, float radius, uint nbPoints, float degrees, QColor color, QObject* parent)
    : Mesh(parent)
{
    setDiscSection(position, radius, nbPoints, degrees, color);
}

void DiscSectionMesh::setDiscSection(QVector3D position, float radius, uint nbPoints, float degrees, QColor color)
{
    clear();
    setGLMode(GL_POLYGON);
    if (nbPoints < 3)
    {
        nbPoints = 3;
    }
    
    float d =M_PI/2.0f;
    float step = (M_PI / ((float)nbPoints * 180.0f)) * (degrees/2.0f);
    addVertex(Vertex(position.x(), position.y(), color, QVector2D(cos(d), sin(d))));
    for (float i = 0; i < nbPoints; i++, d += step)
    {
        float x = cos(d);
        float y = sin(d);
        addVertex(Vertex(x*radius, y*radius, color, QVector2D(x, y)));
    }
    d = M_PI/2.0f;
    for (float i = nbPoints; i > 0; i--, d -= step)
    {
        float x = cos(d);
        float y = sin(d);
        addVertex(Vertex(x*radius, y*radius, color, QVector2D(x, y)));
    }
}
