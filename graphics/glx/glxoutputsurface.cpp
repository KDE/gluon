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

using namespace GluonGraphics::GLX;

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

    if( renderTarget() )
        renderTarget()->renderContents();

    glXSwapBuffers( QX11Info::display(), widget()->winId() );
}

void GLXOutputSurface::setSize(int width, int height)
{
    GluonGraphics::OutputSurface::setSize(width, height);
    glViewport( 0, 0, width, height );
}

void GLXOutputSurface::createDebug()
{

}

#include "glxoutputsurface.moc"
