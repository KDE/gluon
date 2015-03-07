/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
 * Copyright (c) 2015 Felix Rohrbach <kde@fxrh.de>
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

#include "glxqtquickrenderer.h"

#include <QQuickRenderControl>
#include <QQuickWindow>
#include <QQmlEngine>
#include <QOpenGLContext>
#include <QX11Info>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <core/messagehandler.h>
#include <core/gluonvarianttypes.h>
#include <core/log.h>
#include <core/resourcemanager.h>

#include <graphics/texturedata.h>
#include <graphics/spritemesh.h>
#include <graphics/material.h>
#include <graphics/materialinstance.h>
#include <graphics/backend.h>
#include <graphics/mathutils.h>
#include <graphics/defaults.h>

#include "glxbackend.h"
#include "glxbuffer.h"
#include "glxcontext.h"
#include "glxtexturedata.h"
#include "glxrendertarget.h"

using namespace GluonGraphics::GLX;

class GLXQtQuickRenderer::Private
{
    public:
        Private(){}

        QOpenGLContext* glContext;
        GLXRenderTarget* renderTarget;
};

GLXQtQuickRenderer::GLXQtQuickRenderer( QObject* parent )
    : GluonGraphics::QtQuickRenderer( parent ), d( new Private )
{
    d->renderTarget = new GLXRenderTarget();
    d->renderTarget->resize(width(), height());

    connect( quickWindow(), &QQuickWindow::sceneGraphInitialized, this, &GLXQtQuickRenderer::createBuffer );
    connect( quickWindow(), &QQuickWindow::sceneGraphInvalidated, this, &GLXQtQuickRenderer::destroyBuffer );
}

GLXQtQuickRenderer::~GLXQtQuickRenderer()
{
    delete d->renderTarget;
    delete d;
}

GluonGraphics::TextureData* GLXQtQuickRenderer::data() const
{
    return d->renderTarget->texture()->data();
}

void GLXQtQuickRenderer::resize( int width, int height )
{
    GluonGraphics::QtQuickRenderer::resize(width, height);

    d->renderTarget->resize(width, height);

    if( quickLoaded() )
    {
        createBuffer(); // Informs quickWindow about the new size of the buffer
    }
}

void GLXQtQuickRenderer::renderQuick()
{
    GLXBackend* backend = static_cast<GLXBackend*>(GLXBackend::currentBackend());

    d->glContext->makeCurrent( backend->context()->currentWindow() );

    d->renderTarget->bind();
    renderControl()->polishItems();
    renderControl()->sync();
    renderControl()->render();
    d->renderTarget->release();
}

bool GLXQtQuickRenderer::startQuick()
{
    if( !GluonGraphics::QtQuickRenderer::startQuick() )
        return false;

    GLXBackend* backend = qobject_cast<GLXBackend*>( GLXBackend::currentBackend() );

    d->glContext = new QOpenGLContext();
    QGLXNativeContext qglxContext( backend->context()->nativeContext(), QX11Info::display(),
                                   backend->context()->currentWindow()->winId() );
    d->glContext->setNativeHandle( QVariant::fromValue(qglxContext) );
    d->glContext->create();

    d->glContext->makeCurrent(backend->context()->currentWindow());

    renderControl()->initialize( d->glContext );
    return true;
}

void GLXQtQuickRenderer::createBuffer()
{
    quickWindow()->setRenderTarget( d->renderTarget->fbo(), QSize(width(), height()) ); // TODO: respect devicePixelRatio
}

void GLXQtQuickRenderer::destroyBuffer()
{
}
