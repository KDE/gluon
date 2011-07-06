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

#ifdef Q_OS_WIN
#include <GL/glee.h>
#endif

#include <input/inputmanager.h>
#include <graphics/engine.h>
#include <graphics/material.h>
#include <graphics/viewport.h>
#include <graphics/rendertarget.h>

#include <QtOpenGL/QGLFramebufferObject>
#include <QtGui/QGraphicsSceneMouseEvent>
#include <QtGui/QMouseEvent>
#include <QtCore/QCoreApplication>

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
        QPoint pressedPos;
};

RenderableScene::RenderableScene( QObject* parent )
    : QGraphicsScene( parent )
    , d( new RenderableScenePrivate( this ) )
{
    connect( this, SIGNAL( changed( QList<QRectF> ) ), this, SLOT( repaintNeeded() ) );
    connect( this, SIGNAL( sceneRectChanged( QRectF ) ), this, SLOT( repaintNeeded() ) );
    connect( d->target, SIGNAL( framebufferChanged() ), this, SLOT( repaintNeeded() ) );

    connect( Engine::instance(), SIGNAL( currentViewportChanging( Viewport* ) ),
             this, SLOT( newViewport( Viewport* ) ) );
    connect( Engine::instance()->currentViewport(), SIGNAL( viewportSizeChanged( int, int, int, int ) ),
             this, SLOT( viewportSizeChanged( int, int, int, int ) ) );
    connect( GluonInput::InputManager::instance(), SIGNAL( eventFiltered( QEvent* ) ), SLOT( deliverEvent( QEvent* ) ) );

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

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glDepthFunc( GL_LEQUAL );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    d->dirty = false;
}

/*!
    Delivers \a event to this scene. If \a event is a mouse event, then
    \a texCoord indicates the texture co-ordinate on the side of the
    3D object where the user clicked.

    The \a event normally originates from a QWidget or QGraphicsItem that
    contains the 3D object. The caller performs a ray intersection in
    3D space on the position within \a event to determine the \a texCoord
    and then passes \a event on to deliverEvent() for further processing.
*/
void RenderableScene::deliverEvent( QEvent* event )
{
    QRectF bounds = sceneRect();
    int screenX = 0, screenY = 0;

    // Convert the event and deliver it to the scene.
    switch( event->type() )
    {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseMove:
        {
            QMouseEvent* ev = static_cast<QMouseEvent*>( event );
            screenX = qRound( ev->globalPos().x() );
            screenY = qRound( ev->globalPos().y() );
            if( screenX < 0 )
                screenX = 0;
            else if( screenX >= bounds.width() )
                screenX = qRound( bounds.width() - 1 );
            if( screenY < 0 )
                screenY = 0;
            else if( screenY >= bounds.height() )
                screenY = qRound( bounds.height() - 1 );
            d->pressedPos = QPoint( screenX, screenY );

            QEvent::Type type;
            if( ev->type() == QEvent::MouseButtonPress )
                type = QEvent::GraphicsSceneMousePress;
            else if( ev->type() == QEvent::MouseButtonRelease )
                type = QEvent::GraphicsSceneMouseRelease;
            else if( ev->type() == QEvent::MouseButtonDblClick )
                type = QEvent::GraphicsSceneMouseDoubleClick;
            else
                type = QEvent::GraphicsSceneMouseMove;
            QGraphicsSceneMouseEvent e( type );
            e.setPos( QPointF( ev->pos().x(), ev->pos().y() ) );
            e.setScenePos( QPointF( ev->pos().x(), ev->pos().y() ) );
            e.setScreenPos( QPoint( screenX, screenY ) );
            e.setButtonDownScreenPos( ev->button(), d->pressedPos );
            e.setButtonDownScenePos
            ( ev->button(), QPointF( d->pressedPos.x() + bounds.x(),
                                     d->pressedPos.y() + bounds.y() ) );
            e.setButtons( ev->buttons() );
            e.setButton( ev->button() );
            e.setModifiers( ev->modifiers() );
            e.setAccepted( false );
            QCoreApplication::sendEvent( this, &e );
        }
        break;

#ifndef QT_NO_WHEELEVENT
        case QEvent::Wheel:
        {
            QWheelEvent* ev = static_cast<QWheelEvent*>( event );
            QGraphicsSceneWheelEvent e( QEvent::GraphicsSceneWheel );
            e.setPos( QPointF( ev->pos().x(), ev->pos().y() ) );
            e.setScenePos( QPointF( ev->pos().x(), ev->pos().y() ) );
            e.setScreenPos( QPoint( screenX, screenY ) );
            e.setButtons( ev->buttons() );
            e.setModifiers( ev->modifiers() );
            e.setDelta( ev->delta() );
            e.setOrientation( ev->orientation() );
            e.setAccepted( false );
            QCoreApplication::sendEvent( this, &e );
        }
        break;
#endif

        default:
        {
            // Send the event directly without any conversion.
            // Typically used for keyboard, focus, and enter/leave events.
            QCoreApplication::sendEvent( this, event );
        }
        break;

    }
}

void RenderableScene::drawBackground( QPainter* painter, const QRectF& rect )
{
    // Fill the fbo with the transparent color as there won't
    // be a window or graphics item drawing a previous background.
    painter->save();
    painter->setCompositionMode( QPainter::CompositionMode_Source );
    painter->fillRect( rect, Qt::transparent );
    painter->restore();
}

#include "renderablescene.moc"
