/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "glxoutputsurface.h"

#include <manager.h>

#include <QtGui/QWidget>
#include <QtGui/QX11Info>

#include <QMatrix4x4>

#include <GL/gl.h>
#include <GL/glx.h>

#include "glxcontext.h"
#include <rendertarget.h>
#include <spritemesh.h>
#include <shader.h>
#include <backend.h>
#include <mathutils.h>

using namespace GluonGraphics;

class GLXOutputSurface::Private
{
    public:
        GLX::Context* context;

        SpriteMesh* data;
        Shader* shader;
};

GLXOutputSurface::GLXOutputSurface( GLX::Context* context, QWidget* container, QObject* parent )
    : GluonGraphics::OutputSurface( container, parent ), d( new Private )
{
    d->context = context;
}

GLXOutputSurface::~GLXOutputSurface()
{

}

void GLXOutputSurface::renderContents()
{
    d->context->makeCurrent( widget() );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

//     if( renderTarget() )
//         renderTarget()->renderContents();

    d->shader->bind();

    d->shader->setProperty( "modelMatrix", QMatrix4x4() );
    d->shader->setProperty( "viewMatrix", QMatrix4x4() );
    QMatrix4x4 proj;
    proj.ortho(-2, 2, -2, 2, -2, 2);
    d->shader->setProperty( "projectionMatrix", proj );

    d->data->render( d->shader );

    d->shader->release();

    glXSwapBuffers( QX11Info::display(), widget()->winId() );
}

void GLXOutputSurface::setSize(int width, int height)
{
    GluonGraphics::OutputSurface::setSize(width, height);
    glViewport( 0, 0, width, height );
}

void GLXOutputSurface::createDebug()
{
    d->data = new SpriteMesh();
    d->data->initialize();

    d->shader = Manager::instance()->backend()->createShader();

    d->shader->setSource( Shader::VertexProgramSource, "uniform mat4 modelMatrix;\n\
uniform mat4 viewMatrix;\n\
uniform mat4 projectionMatrix;\n\
attribute vec3 vertex;\n\
void main() {\n\
mat4 modelViewProj = (modelMatrix * viewMatrix) * projectionMatrix;\n\
gl_Position = vec4(vertex, 1.0) * modelViewProj; } " );
    d->shader->setSource( Shader::FragmentProgramSource, "void main() { gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0); }");

    if( !d->shader->build() )
        qWarning( d->shader->error().toUtf8() );
}

#include "glxoutputsurface.moc"
