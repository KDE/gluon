/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Giulio Camuffo <giuliocamuffo@gmail.com>
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

#include "renderablescene.h"

#include <QGLFramebufferObject>

#include <graphics/engine.h>
#include <graphics/material.h>
#include <graphics/viewport.h>
#include <graphics/rendertarget.h>

using namespace GluonEngine;
using namespace GluonGraphics;

class RenderableScene::RenderableScenePrivate
{
    public:
        RenderableScenePrivate( RenderableScene* scene )
            : q( scene )
            , target( new RenderTarget( scene ) )
            , dirty( true )
        {
            const int w = Engine::instance()->currentViewport()->width();
            const int h = Engine::instance()->currentViewport()->height();
            if( QGLContext::currentContext() )
            {
                target->setFramebufferObject( new QGLFramebufferObject( w, h, QGLFramebufferObject::CombinedDepthStencil ) );
            }
            target->setMaterialInstance( Engine::instance()->material( "default" )->createInstance( "qmlTarget" ) );

            viewportSizeChanged( 0, 0, w, h );
        }

        void newViewport( Viewport* viewport )
        {
            q->disconnect( Engine::instance()->currentViewport(), SIGNAL( viewportSizeChanged( int, int, int, int ) ),
                           q, SLOT( viewportSizeChanged( int, int, int, int ) ) );
            q->connect( viewport, SIGNAL( viewportSizeChanged( int, int, int, int ) ),
                        q, SLOT( viewportSizeChanged( int, int, int, int ) ) );
        }

        void viewportSizeChanged( int left, int bottom, int width, int height )
        {
            q->setSceneRect( QRectF( 0, 0, width, height ) );
        }

        void repaintNeeded()
        {
            dirty = true;
        }

        RenderableScene* q;
        RenderTarget* target;
        bool dirty;
};

RenderableScene::RenderableScene( QObject* parent )
               : QGraphicsScene( parent )
               , d( new RenderableScenePrivate( this ) )
{
    connect( this, SIGNAL( changed(QList<QRectF>) ), this, SLOT( repaintNeeded() ) );
    connect( this, SIGNAL( sceneRectChanged(QRectF) ), this, SLOT( repaintNeeded() ) );
    connect( d->target, SIGNAL( framebufferChanged() ), this, SLOT( repaintNeeded() ) );

    connect( Engine::instance(), SIGNAL( currentViewportChanging( Viewport* ) ),
             this, SLOT( newViewport( Viewport* ) ) );
    connect( Engine::instance()->currentViewport(), SIGNAL( viewportSizeChanged( int, int, int, int ) ),
             this, SLOT( viewportSizeChanged( int, int, int, int ) ) );

    Engine::instance()->addRenderTarget( d->target, 0 );
}

RenderableScene::~RenderableScene()
{
    delete d;
}

void RenderableScene::renderScene()
{
    if( !d->dirty || !QGLContext::currentContext() )
    {
        return;
    }

    if( !d->target->framebufferObject() )
    {
        const int w = Engine::instance()->currentViewport()->width();
        const int h = Engine::instance()->currentViewport()->height();
        d->target->setFramebufferObject( new QGLFramebufferObject( w, h, QGLFramebufferObject::CombinedDepthStencil ) );
    }

    d->target->bind();

    QSize size = QSize( sceneRect().size().toSize() );
    QPainter painter( d->target->framebufferObject() );
    painter.setWindow( 0, 0, size.width(), size.height() );
    painter.setViewport( 0, 0, size.width(), size.height() );
    render( &painter );
    painter.end();

    d->target->release();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthFunc(GL_LEQUAL);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    d->dirty = false;
}

void RenderableScene::drawBackground( QPainter* painter, const QRectF& rect )
{
    // Fill the fbo with the transparent color as there won't
    // be a window or graphics item drawing a previous background.
    painter->save();
    painter->setCompositionMode(QPainter::CompositionMode_Source);
    painter->fillRect(rect, Qt::transparent);
    painter->restore();
}

#include "renderablescene.moc"
