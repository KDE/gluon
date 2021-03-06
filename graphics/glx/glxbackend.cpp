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
#include <QtCore/QCoreApplication>
#include <QtGui/QWindow>
#include <QtX11Extras/QX11Info>

#include <GL/gl.h>
#include <GL/glx.h>

#include <core/log.h>

#include "glxcontext.h"
#include "glxshader.h"
#include "glxoutputsurface.h"
#include "glxbuffer.h"
#include "glxtexturedata.h"
#include "glxrendertarget.h"
#include "glxmeshdata.h"
#include "glxqtquickrenderer.h"

using namespace GluonGraphics::GLX;

class GLXBackend::Private
{
    public:
        Context* context = nullptr;

        QString errorString;
};

GLXBackend::GLXBackend()
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

bool GLXBackend::initialize( WId id )
{
    if( d->context )
        return true;

    d->context = new Context();

    if( !d->context->initialize( id ) )
    {
        d->errorString = d->context->errorString();
        return false;
    }

    INFO() << information( GluonGraphics::Backend::SummaryInformation );

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

GluonGraphics::OutputSurface* GLXBackend::createOutputSurface( QWindow* window )
{
    return new GLXOutputSurface( d->context, window, window );
}

GluonGraphics::MeshData* GLXBackend::createMeshData()
{
    return new GLXMeshData();
}

GluonGraphics::QtQuickRenderer* GLXBackend::createQuickRenderer( QObject* parent )
{
    return new GLXQtQuickRenderer(parent);
}

bool GLXBackend::isBufferTypeSuported( GluonGraphics::Buffer::BufferType type )
{
    switch( type )
    {
        case GluonGraphics::Buffer::Vertex:
        case GluonGraphics::Buffer::Index:
            return true;
        default:
            return false;
        //TODO: Implement support for more buffer types.
    }
}
