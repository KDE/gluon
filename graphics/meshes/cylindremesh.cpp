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

#include "cylindremesh.h"
namespace GluonGraphics
{
    CylindreMesh::CylindreMesh(QObject * parent)
            : Mesh(parent)
    {
        setCylindre(3, 5, 10);
    }

    void CylindreMesh::setCylindre(float radius, float height, unsigned int nbPoints)
    {

        clear();
        m_radius = radius;
        m_height = height;
        m_nbPoints = nbPoints;
        setGLMode(GL_TRIANGLE_STRIP);

        float step = M_PI * 2 / (float)nbPoints;

        for (float i = 0; i < M_PI*2; i += step)
        {
            float x = cos(i) ;
            float y = sin(i) ;
            addVertex(Vertex(x*radius, y*radius, 0, Qt::white, QVector2D(x, y)));
            addVertex(Vertex(x*radius, y*radius, height, Qt::white, QVector2D(x, y)));

        }

        addVertex(Vertex(1*radius, 0*radius, 0, Qt::white, QVector2D(1, 0)));
        addVertex(Vertex(1*radius, 0*radius, height, Qt::white, QVector2D(1, 0)));

    }
}
