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

#include <graphics/manager.h>

#include "glxcontext.h"
#include "glxshader.h"
#include "glxoutputsurface.h"
#include "glxbuffer.h"
#include "glxtexturedata.h"
#include "glxrendertarget.h"
#include "glxmeshdata.h"

using namespace GluonGraphics::GLX;

class GLXBackend::Private
{
    public:
        Private() : context( 0 ) { }

        Context* context;

        QString errorString;
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
    delete d;
}

bool GLXBackend::initialize( QWidget* widget )
{
    if( d->context )
        return true;

    d->context = new Context();

    if( !d->context->initialize( widget ) )
    {
        d->errorString = d->context->errorString();
        return false;
    }

    DEBUG_BLOCK
    DEBUG_TEXT( information( FullInformation ) );

    return true;
}

QString GLXBackend::errorString()
{
    return d->errorString;
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
            info << "GluonGraphics GLX Backend using OpenGL " << d->context->glVersion().toString();
            break;
        case FullInformation:
            info << "-------------------------------------------------------------\n"
                 << "                 GluonGraphics GLX Backend\n"
                 << " GLX Version:  " << d->context->glXVersion().toString() << "\n"
                 << " GL Version:   " << d->context->glVersion().toString() << "\n"
                 << " GLSL Version: " << d->context->glslVersion().toString() << "\n"
                 << " Renderer:     " << d->context->rendererString() << "\n"
                 << "\n"
                 << "-------------------------------------------------------------\n";
            break;
        case VerboseInformation:
            info << information( FullInformation );
            info << "\nNumber of extensions: " << d->context->extensions().count() << "\n"
                 << "All extensions:\n";

            foreach( const QString& extension, d->context->extensions() )
                info << extension << ", ";

            break;
    }
    info.seek( 0 );
    return info.readAll();
}

Context* GLXBackend::context()
{
    return d->context;
}

GluonGraphics::Buffer* GLXBackend::createBuffer()
{
    return new GLXBuffer();
}

GluonGraphics::TextureData* GLXBackend::createTextureData()
{
    return new GLXTextureData();
}

GluonGraphics::RenderTarget* GLXBackend::createRenderTarget()
{
    return new GLXRenderTarget();
}

GluonGraphics::Shader* GLXBackend::createShader()
{
    return new GLXShader();
}

GluonGraphics::OutputSurface* GLXBackend::createOutputSurface( QWidget* widget )
{
    return new GLXOutputSurface( d->context, widget, widget );
}

GluonGraphics::MeshData* GLXBackend::createMeshData()
{
    return new GLXMeshData();
}

Q_EXPORT_PLUGIN2( gluongraphics_glx_backend, GluonGraphics::GLX::GLXBackend )

#include "glxbackend.moc"
