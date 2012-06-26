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
#include "texture.h"

using namespace GluonGraphics;

class RenderTarget::Private
{
    public:
        Private( RenderTarget* qq ) : q( qq ), mesh( 0 ), shader( 0 ), texture( 0 ) { }
        void createShader();

        RenderTarget* q;

        int width;
        int height;

        QList< RenderPipelineItem* > children;

        Mesh* mesh;
        Shader* shader;

        Texture* texture;
};

RenderTarget::RenderTarget( QObject* parent )
    : QObject( parent ), d( new Private( this ) )
{
    d->mesh = Manager::instance()->resource< SpriteMesh >( Manager::Defaults::SpriteMesh );
}

RenderTarget::RenderTarget( int width, int height, QObject* parent )
    : QObject( parent ), d( new Private( this ) )
{
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

    if( !d->shader )
        d->createShader();

    d->shader->bind();
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

Texture* RenderTarget::texture()
{
    if( !d->texture )
        d->texture = new Texture( textureData(), this );

    return d->texture;
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
uniform sampler2D texture1;\n\
varying vec2 out_uv;\n\
void main() { gl_FragColor = texture2D(texture0, out_uv) * texture2D(texture1, out_uv); }");

    if( !shader->build() )
    {
        qWarning( shader->error().toUtf8() );
        return;
    }

    shader->setUniform( "modelMatrix", QMatrix4x4() );
    shader->setUniform( "viewMatrix", QMatrix4x4() );
    QMatrix4x4 matrix;
    matrix.ortho( -.5f, .5f, -.5f, .5f, -.5f, .5f );
    shader->setUniform( "projectionMatrix", matrix );
    shader->setUniform( "texture0", QVariant::fromValue< GluonGraphics::Texture* >( q->texture() ) );
    shader->setUniform( "texture1", QVariant::fromValue< GluonGraphics::Texture* >( Manager::instance()->resource< Texture >( Manager::Defaults::Texture ) ) );
}

#include "rendertarget.moc"
