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
#include <graphics/rendertarget.h>

using namespace GluonEngine;
using namespace GluonGraphics;

class RenderableScene::RenderableScenePrivate
{
    public:
        RenderableScenePrivate( RenderableScene* scene )
            : q( scene )
            , target( new RenderTarget( scene ) )
            , fbo( 0 )
            , dirty( true )
        {
            fbo = new QGLFramebufferObject( 500, 500, QGLFramebufferObject::CombinedDepthStencil );
            target->setFramebufferObject( fbo );
            target->setMaterialInstance( Engine::instance()->material( "default" )->createInstance( "qmlTarget" ) );
        }

        void repaintNeeded()
        {
            dirty = true;
        }

        RenderableScene* q;
        RenderTarget* target;
        QGLFramebufferObject* fbo;
        bool dirty;
};

RenderableScene::RenderableScene( QObject* parent )
               : QGraphicsScene( parent )
               , d( new RenderableScenePrivate( this ) )
{
    connect( this, SIGNAL(changed(QList<QRectF>)), this, SLOT( repaintNeeded() ));
    connect( this, SIGNAL(sceneRectChanged(QRectF)), this, SLOT( repaintNeeded() ));

    Engine::instance()->addRenderTarget( d->target, 0 );
}

RenderableScene::~RenderableScene()
{
    delete d;
}

void RenderableScene::renderScene()
{
    if( !d->dirty )
    {
        return;
    }

    d->target->bind();

    QSize size = QSize( 500, 500 );
    QPainter painter( d->fbo );
    painter.setWindow( 0, 0, size.width(), size.height() );
    painter.setViewport( 0, 0, size.width(), size.height() );
    render( &painter );
    painter.end();

    d->target->release();

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
