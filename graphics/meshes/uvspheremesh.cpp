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

#include "uvspheremesh.h"
#include <cmath>
namespace GluonGraphics
{
    UvSphereMesh::UvSphereMesh(QObject * parent)
            : Mesh(parent)
    {
        setUvSphere(5, 4);
    }


    void UvSphereMesh::setUvSphere(float radius, int division)
    {

        clear();
        setGLMode(GL_POLYGON);
        float  t = (1.0 + sqrt(5.0)) / 2.0;

        addVertex(QVector3D(-1,  t,  0));
        addVertex(QVector3D(1,  t,  0));
        addVertex(QVector3D(-1, -t,  0));
        addVertex(QVector3D(1, -t,  0));


        addVertex(QVector3D(0, -1,  t));
        addVertex(QVector3D(0,  1,  t));
        addVertex(QVector3D(0, -1, -t));
        addVertex(QVector3D(0,  1, -t));

        addVertex(QVector3D(t,  0, -1));
        addVertex(QVector3D(t,  0,  1));
        addVertex(QVector3D(-t,  0, -1));
        addVertex(QVector3D(-t,  0,  1));

    }

}
