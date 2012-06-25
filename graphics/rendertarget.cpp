/*****************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010-2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include <QMatrix4x4>

#include "renderpipelineitem.h"
#include "manager.h"
#include "backend.h"
#include "shader.h"
#include "spritemesh.h"

#include <GL/gl.h>

using namespace GluonGraphics;

class RenderTarget::Private
{
    public:
        void createShader();
        int width;
        int height;

        QList< RenderPipelineItem* > children;

        Mesh* mesh;
        Shader* shader;
};

RenderTarget::RenderTarget( QObject* parent )
    : QObject( parent ), d( new Private )
{
    d->createShader();
    d->mesh = Manager::instance()->resource< SpriteMesh >( Manager::Defaults::SpriteMesh );
}

RenderTarget::RenderTarget( int width, int height, QObject* parent )
    : QObject( parent ), d( new Private )
{
    d->createShader();
    d->mesh = Manager::instance()->resource< SpriteMesh >( Manager::Defaults::SpriteMesh );
    resize(width, height);
}

RenderTarget::~RenderTarget()
{
    delete d;
}

void RenderTarget::addChild(RenderPipelineItem* item)
{
    if( !d->children.contains(item) )
        d->children.append(item);
}

void RenderTarget::removeChild(RenderPipelineItem* item)
{
    d->children.removeOne( item );
}

int RenderTarget::height()
{
    return d->height;
}

int RenderTarget::width()
{
    return d->width;
}

void RenderTarget::update()
{
    bind();

    Q_FOREACH( RenderPipelineItem* item, d->children )
    {
        item->renderContents();
    }

    release();
}

void RenderTarget::renderContents()
{
    update();

    d->shader->bind();
    d->shader->setProperty( "modelMatrix", QMatrix4x4() );
    d->shader->setProperty( "viewMatrix", QMatrix4x4() );
    QMatrix4x4 proj;
    proj.ortho( -.5f, .5f, -.5f, .5f, -.5f, .5f );
    d->shader->setProperty( "projectionMatrix", proj );

    bindTexture();
    d->shader->setProperty( "texture0", QVariant::fromValue<int>( 0 ) );

    d->mesh->render( d->shader );
    d->shader->release();
}

void RenderTarget::resize( int width, int height )
{
    if( width == d->width && height == d->height )
        return;

    d->width = width;
    d->height = height;

    resizeImpl();
}

void RenderTarget::Private::createShader()
{
    shader = Manager::instance()->backend()->createShader();

    shader->setSource( Shader::VertexProgramSource, "uniform mat4 modelMatrix;\n\
uniform mat4 viewMatrix;\n\
uniform mat4 projectionMatrix;\n\
attribute vec3 vertex;\n\
attribute vec2 uv0;\n\
varying vec2 out_uv;\n\
void main() {\n\
out_uv = uv0;\n\
gl_Position = vec4(vertex, 1.0) * (modelMatrix * viewMatrix) * projectionMatrix; } " );
    shader->setSource( Shader::FragmentProgramSource, "uniform sampler2D texture0;\n\
varying vec2 out_uv;\n\
void main() { gl_FragColor = texture2D(texture0, out_uv) + vec4(out_uv.x, out_uv.y, 1.0, 1.0); }");

    if( !shader->build() )
        qWarning( shader->error().toUtf8() );
}

#include "rendertarget.moc"
