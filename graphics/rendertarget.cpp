/*****************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "rendertarget.h"

#include <QtGui/QMatrix4x4>

#include "texture.h"
#include "vertexbuffer.h"
#include "vertexattribute.h"
#include "materialinstance.h"
#include "engine.h"
#include "viewport.h"

using namespace GluonGraphics;

class RenderTarget::Private
{
    public:
        Private(RenderTarget* qq)
            : q(qq), frameBuffer(0), texture(0), renderable( true ), vertexData(0),
            modelMatrix(QMatrix4x4()), viewMatrix(QMatrix4x4())
        { }
        ~Private() { }

        void createVertexData();

        RenderTarget* const q;

        QGLFramebufferObject* frameBuffer;
        Texture* texture;

        bool renderable;

        MaterialInstance* material;

        VertexBuffer* vertexData;

        const QMatrix4x4 modelMatrix;
        const QMatrix4x4 viewMatrix;
        QMatrix4x4 projectionMatrix;
};

RenderTarget::RenderTarget( QObject* parent )
    : QObject( parent ), d( new Private(this) )
{
    d->createVertexData();
    d->projectionMatrix.ortho(-1, 1, -1, 1, -1, 1);
}

RenderTarget::RenderTarget( int width, int height, QObject* parent )
    : QObject( parent ), d( new Private(this) )
{
    d->frameBuffer = new QGLFramebufferObject(width, height, QGLFramebufferObject::Depth);
    d->createVertexData();
    d->projectionMatrix.ortho(-1, 1, -1, 1, -1, 1);
}

RenderTarget::~RenderTarget()
{
    if(d->vertexData)
        delete d->vertexData;
    if(d->frameBuffer)
        delete d->frameBuffer;
    delete d;
}

bool RenderTarget::isRenderable() const
{
    return d->renderable;
}

void RenderTarget::setRenderable( bool render )
{
    if( render )
    {
        if(!d->renderable)
            d->createVertexData();
        d->renderable = true;
    }
    else
    {
        if(d->renderable)
        {
            delete d->vertexData;
            d->vertexData = 0;
        }
        d->renderable = false;
    }
}

void RenderTarget::setFramebufferObject( QGLFramebufferObject* fbo )
{
    d->frameBuffer = fbo;

    emit framebufferChanged();
}

void RenderTarget::setMaterialInstance( MaterialInstance* material )
{
    Q_ASSERT(material);
    d->material = material;
    d->material->setUseCustomViewProjMatrices(true);
    d->material->setProperty("modelMatrix", d->modelMatrix);
    d->material->setProperty("viewMatrix", d->viewMatrix);
    d->material->setProperty("projectionMatrix", d->projectionMatrix);

    if(d->frameBuffer)
        d->material->setProperty("texture0", d->frameBuffer->texture());
}

void RenderTarget::resize( int width, int height )
{
    if(d->frameBuffer && QGLContext::currentContext())
    {
        QGLFramebufferObject::Attachment attachment = d->frameBuffer->attachment();

        delete d->frameBuffer;
        d->frameBuffer = new QGLFramebufferObject(width, height, attachment);
        d->material->setProperty("texture0", d->frameBuffer->texture());

        emit framebufferChanged();
    }
}

void RenderTarget::bind()
{
    if(d->frameBuffer)
    {
        if(!d->frameBuffer->bind())
            qDebug() << "Failed to bind FBO";
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void RenderTarget::release()
{
    if(d->frameBuffer)
        d->frameBuffer->release();

}

MaterialInstance* RenderTarget::materialInstance()
{
    return d->material;
}

QGLFramebufferObject* RenderTarget::framebufferObject() const
{
    return d->frameBuffer;
}

void RenderTarget::render()
{
    if(!d->renderable)
        return;

    d->material->bind();
    d->vertexData->render(VertexBuffer::RM_TRIANGLES, d->material);
    d->material->release();
}

void RenderTarget::Private::createVertexData()
{
    if(vertexData)
        delete vertexData;

    vertexData = new VertexBuffer(q);

    VertexAttribute vert("vertex", 3);
    vert << -1.0f << -1.0f << 0.0f;
    vert << -1.0f <<  1.0f << 0.0f;
    vert <<  1.0f <<  1.0f << 0.0f;
    vert <<  1.0f << -1.0f << 0.0f;
    vertexData->addAttribute(vert);

    VertexAttribute uv0("uv0", 2);
    uv0 << 0.0f << 0.0f;
    uv0 << 0.0f << 1.0f;
    uv0 << 1.0f << 1.0f;
    uv0 << 1.0f << 0.0f;
    vertexData->addAttribute(uv0);

    QVector<uint> indices;
    indices << 0 << 1 << 2;
    indices << 0 << 2 << 3;
    vertexData->setIndices(indices);

    vertexData->initialize();
}

#include "rendertarget.moc"
