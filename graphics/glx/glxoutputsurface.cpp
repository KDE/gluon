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

#include <QtGui/QWindow>
#include <QtX11Extras/QX11Info>

#include <GL/gl.h>
#include <GL/glx.h>
#undef Bool // see http://eigen.tuxfamily.org/bz/show_bug.cgi?id=253 (but Qt related)
#undef CursorShape // see http://eigen.tuxfamily.org/bz/show_bug.cgi?id=253 (but Qt related)
#undef Success // see http://eigen.tuxfamily.org/bz/show_bug.cgi?id=253

#include <graphics/manager.h>
#include <graphics/rendertarget.h>
#include <graphics/spritemesh.h>
#include <graphics/shader.h>
#include <graphics/backend.h>
#include <graphics/mathutils.h>

#include "glxcontext.h"

using namespace GluonGraphics::GLX;

class GLXOutputSurface::Private
{
    public:
        Private() : firstFrame( true ) { }

        GLX::Context* context;

        SpriteMesh* data;
        Shader* shader;

        //Workaround for radeon bug
        bool firstFrame;
};

GLXOutputSurface::GLXOutputSurface( GLX::Context* context, QWindow* container, QObject* parent )
    : GluonGraphics::OutputSurface( container, parent ), d( new Private )
{
    d->context = context;
}

GLXOutputSurface::~GLXOutputSurface()
{

}

void GLXOutputSurface::renderContents()
{
    d->context->makeCurrent( window() );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* This is a workaround for a radeon bug.
     *
     * The sequence glEnable( GL_DEPTH_TEST ) glClear() ... draw calls ... glSwapBuffers() glClear()
     * will fail to do depth testing properly, whereas the sequence glClear()
     * glEnable( GL_DEPTH_TEST ) ... draw calls ... glSwapBuffers glClear() will work fine.
     */
    if( d->firstFrame )
    {
        glEnable( GL_DEPTH_TEST );
        d->firstFrame = false;
    }

    if( renderTarget() )
        renderTarget()->renderContents();

    glXSwapBuffers( QX11Info::display(), window()->winId() );
}

void GLXOutputSurface::setSize(int width, int height)
{
    GluonGraphics::OutputSurface::setSize(width, height);
    glViewport( 0, 0, width, height );
}

void GLXOutputSurface::createDebug()
{

}

 
