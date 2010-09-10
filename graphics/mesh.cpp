/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "mesh.h"
#include "materialinstance.h"

#include <GL/gl.h>
#include <GL/glext.h>

#include <QtGui/QMatrix4x4>
#include "math.h"

using namespace GluonGraphics;

class Mesh::MeshPrivate
{
    public:
        MeshPrivate() { buffer = 0; }

        MaterialInstance * material;

        GLuint buffer;
        int colorOffset;
        int uvOffset;
};

Mesh::Mesh(QObject * parent)
    : QObject(parent),
      d(new MeshPrivate)
{

}

Mesh::~Mesh()
{
    delete d;
}

void
Mesh::load( const QString& filename )
{
    if(d->buffer)
        return;

    float vertices[] = {
        -1.f, -1.f, 0.f,
        -1.f,  1.f, 0.f,
         1.f,  1.f, 0.f,

        -1.f, -1.f, 0.f,
         1.f,  1.f, 0.f,
         1.f, -1.f, 0.f,
    };
    float colors[] = {
        1.f, 0.f, 0.f, 1.f,
        0.f, 1.f, 0.f, 1.f,
        0.f, 0.f, 1.f, 1.f,

        1.f, 0.f, 0.f, 1.f,
        0.f, 0.f, 1.f, 1.f,
        1.f, 1.f, 0.f, 1.f,
    };
    float uvs[] = {
        0.f, 0.f,
        0.f, 1.f,
        1.f, 1.f,

        0.f, 0.f,
        1.f, 1.f,
        1.f, 0.f,
    };

    glGenBuffers(1, &d->buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d->buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors) + sizeof(uvs), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    d->colorOffset = sizeof(vertices);
    glBufferSubData(GL_ARRAY_BUFFER, d->colorOffset, sizeof(colors), colors);
    d->uvOffset = d->colorOffset + sizeof(colors);
    glBufferSubData(GL_ARRAY_BUFFER, d->uvOffset, sizeof(uvs), uvs);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
Mesh::render( const QMatrix4x4& modelViewProj )
{
    d->material->bind();
    d->material->setModelViewProjectionMatrix(modelViewProj);
    glBindBuffer(GL_ARRAY_BUFFER, d->buffer);
    glVertexAttribPointer(d->material->attributeLocation("vertex"), 3, GL_FLOAT, 0, 0, 0);
    glVertexAttribPointer(d->material->attributeLocation("color"), 4, GL_FLOAT, 0, 0, (void*)(d->colorOffset) );
    glVertexAttribPointer(d->material->attributeLocation("uv0"), 2, GL_FLOAT, 0, 0, (void*)(d->uvOffset) );

    glEnableVertexAttribArray(d->material->attributeLocation("vertex"));
    glEnableVertexAttribArray(d->material->attributeLocation("color"));
    glEnableVertexAttribArray(d->material->attributeLocation("uv0"));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(d->material->attributeLocation("vertex"));
    glDisableVertexAttribArray(d->material->attributeLocation("color"));
    glDisableVertexAttribArray(d->material->attributeLocation("uv0"));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    d->material->release();
}

void
Mesh::setMaterial( MaterialInstance* material )
{
    d->material = material;
}

#include "mesh.moc"
