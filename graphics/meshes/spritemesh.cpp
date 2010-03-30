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

#include "spritemesh.h"

using namespace GluonGraphics;

class SpriteMesh::SpriteMeshPrivate
{
    public:
        QSizeF size;
};

SpriteMesh::SpriteMesh(QObject * parent)
        : Mesh(parent)
{
    d = new SpriteMeshPrivate;
    setSize(QSizeF(1.0f, 1.0f));
}

SpriteMesh::SpriteMesh(const QSizeF& size, QObject* parent)
        : Mesh(parent)
{
    d = new SpriteMeshPrivate;
    setSize(size);
}

SpriteMesh::~SpriteMesh()
{
    delete d;
}

void
SpriteMesh::setSize(const QSizeF &size)
{
    d->size = size;

    float halfw = size.width() / 2.0f;
    float halfh = size.height() / 2.0f;

    if (vertexCount() < 4)
    {
        for (int i = 0; i < 4; ++i)
        {
            addVertex(QVector2D());
        }
    }

    Vertex *vertex = vertexAt(0);
    vertex->setX(-halfw);
    vertex->setY(-halfh);
    vertex->setTex(QVector2D(0, 1));
    vertex->setColor(Qt::white);

    vertex = vertexAt(1);
    vertex->setX(-halfw);
    vertex->setY(halfh);
    vertex->setTex(QVector2D(0, 0));
    vertex->setColor(Qt::white);

    vertex = vertexAt(2);
    vertex->setX(halfw);
    vertex->setY(halfh);
    vertex->setTex(QVector2D(1, 0));
    vertex->setColor(Qt::white);

    vertex = vertexAt(3);
    vertex->setX(halfw);
    vertex->setY(-halfh);
    vertex->setTex(QVector2D(1, 1));
    vertex->setColor(Qt::white);
}

QSizeF GluonGraphics::SpriteMesh::size() const
{
    return d->size;
}

