/*****************************************************************************
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

#include "glxbackend.h"

#include <QtCore/QTextStream>
#include <QtGui/QX11Info>
#include <QtGui/QWidget>
#include <QtGui/QApplication>

#include <GL/gl.h>
#include <GL/glx.h>

#include <core/debughelper.h>

#include "glxcontext.h"
#include "glxshader.h"
#include "glxoutputsurface.h"
#include "glxbuffer.h"
#include "glxtexture.h"
#include "glxrendertarget.h"
#include <manager.h>

using namespace GluonGraphics;

class GLXBackend::Private
{
    public:
        Private() : context( 0 ) { }

        GLX::Context* context;
};

GLXBackend::GLXBackend() : d( new Private )
{
}

GLXBackend::~GLXBackend()
{
    if( d->context )
    {
        d->context->clearCurrent();
        delete d->context;
    }
}

void GLXBackend::initialize( QWidget* widget )
{
    if( d->context )
        return;

    d->context = new GLX::Context();
    d->context->makeCurrent( widget );

    DEBUG_BLOCK
    DEBUG_TEXT( information( FullInformation ) );

    glClearColor( 0.f, 0.f, 0.f, 0.f );
}

QString GLXBackend::identifier()
{
    return QString("glx");
}

QString GLXBackend::information( Backend::InformationLevel level )
{
    QTextStream info( QByteArray(), QIODevice::ReadWrite );
    switch( level )
    {
        case SummaryInformation:
            info << "GluonGraphics GLX Backend using OpenGL " << glGetString( GL_VERSION );
            break;
        case FullInformation:
            info << "-------------------------------------------------------------\n"
                 << "                 GluonGraphics GLX Backend\n"
                 << " GLX Version:  " << glXGetClientString( QX11Info::display(), GLX_VERSION ) << "\n"
                 << " GL Version:   " << reinterpret_cast< const char* >( glGetString( GL_VERSION ) ) << "\n"
                 << " GLSL Version: " << reinterpret_cast< const char* >( glGetString( GL_SHADING_LANGUAGE_VERSION ) ) << "\n"
                 << " Renderer:     " << reinterpret_cast< const char* >( glGetString( GL_RENDERER ) ) << "\n"
                 << "\n"
                 << "-------------------------------------------------------------\n";
            break;
        case VerboseInformation:
            info << information( FullInformation );

            int extensionCount;
            glGetIntegerv( GL_NUM_EXTENSIONS, &extensionCount );
            info << "\nNumber of extensions: " << extensionCount << "\n"
                 << "All extensions:\n"
                 << reinterpret_cast< const char* >( glGetString( GL_EXTENSIONS ) );
            break;
    }
    info.seek( 0 );
    return info.readAll();
}

GLX::Context* GLXBackend::context()
{
    return d->context;
}

Buffer* GLXBackend::createBuffer()
{
    return new GLXBuffer();
}

Texture* GLXBackend::createTexture()
{
    return new GLXTexture();
}

RenderTarget* GLXBackend::createRenderTarget()
{
    return new GLXRenderTarget();
}

Shader* GLXBackend::createShader()
{
    return new GLXShader( d->context );
}

OutputSurface* GLXBackend::createOutputSurface( QWidget* widget )
{
    return new GLXOutputSurface( d->context, widget, widget );
}

Q_EXPORT_PLUGIN2( gluongraphics_glx_backend, GluonGraphics::GLXBackend )

#include "glxbackend.moc"
