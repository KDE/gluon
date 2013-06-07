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

#include "qtquickrenderer.h"

#include <QtCore>
#include <QGraphicsScene>
#include <QDeclarativeError>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeItem>
#include <QDeclarativeContext>
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <core/messagehandler.h>
#include <core/gluonvarianttypes.h>

#include "texturedata.h"
#include "spritemesh.h"
#include "material.h"
#include "materialinstance.h"
#include "manager.h"
#include "backend.h"
#include "mathutils.h"

using namespace GluonGraphics;

class QtQuickRenderer::Private
{
    public:
        Private() : buffer( 0 ), root( 0 ), data( 0 ) { }

        void createEngine();

        QImage* buffer;

        QGraphicsScene* scene;
        QDeclarativeContext* context;
        QDeclarativeItem* root;

        SpriteMesh* mesh;
        MaterialInstance* material;

        TextureData* data;

        static QDeclarativeEngine* engine;
};

QDeclarativeEngine* QtQuickRenderer::Private::engine = 0;

QtQuickRenderer::QtQuickRenderer( QObject* parent )
    : Texture( parent ), d( new Private )
{
    //TODO: Make this configurable
    setZDepth( 1.0f );

    d->mesh = Manager::instance()->resource< SpriteMesh >( Manager::Defaults::SpriteMesh );
    d->material = Manager::instance()->resource< Material >( Manager::Defaults::Material )->createInstance();
    Eigen::Affine3f proj = MathUtils::ortho( -0.5, 0.5, -0.5, 0.5, -2, 2);
    d->material->setProperty( "projectionMatrix", QVariant::fromValue(proj) );
    Eigen::Affine3f id = Eigen::Affine3f::Identity();
    d->material->setProperty( "viewMatrix", QVariant::fromValue(id) );
    d->material->setProperty( "modelMatrix", QVariant::fromValue(id) );
    d->material->setProperty( "texture0", QVariant::fromValue< Texture* >( this ) );

    if( !d->engine )
        d->createEngine();
}

QtQuickRenderer::~QtQuickRenderer()
{
    delete d->buffer;
    delete d->data;
    delete d;
}

void QtQuickRenderer::update()
{
    if( !d->root )
        return;

    d->buffer->fill( Qt::transparent );

    QPainter painter( d->buffer );
    d->scene->render( &painter );
    painter.end();

    qImageToGL( d->buffer );
    d->data->setData( d->buffer->width(), d->buffer->height(), d->buffer->bits() );
}

void QtQuickRenderer::renderContents()
{
    if( !d->root )
        return;

    update();

    d->material->bind();
    d->mesh->render( d->material->shader() );
    d->material->release();
}

bool QtQuickRenderer::load( const QUrl& url )
{
    if( d->root )
        return true;

    d->scene = new QGraphicsScene( 0, 0, 1024, 1024, this );
    d->context = new QDeclarativeContext( d->engine->rootContext(), this );

    QDeclarativeComponent comp( d->engine, url );
    d->root = qobject_cast<QDeclarativeItem*>( comp.create( d->context ) );
    d->root->setWidth( 1024 );
    d->root->setHeight( 1024 );

    d->scene->addItem( d->root );

    if( comp.errors().count() > 0 )
    {
        DEBUG_BLOCK
        Q_FOREACH( QDeclarativeError error, comp.errors() )
        {
            DEBUG_TEXT( error.toString() );
        }
        return false;
    }

    d->data = Manager::instance()->backend()->createTextureData();
    d->data->setFilteringMode( TextureData::NearestFilteringMode );
    d->buffer = new QImage( 1024, 1024, QImage::Format_ARGB32 );

    return true;
}

QImage QtQuickRenderer::image() const
{
    return *(d->buffer);
}

TextureData* QtQuickRenderer::data() const
{
    return d->data;
}

QDeclarativeContext* QtQuickRenderer::context() const
{
    return d->context;
}

void QtQuickRenderer::resize( int width, int height )
{
    if( d->buffer )
        delete d->buffer;

    d->buffer = new QImage( width, height, QImage::Format_ARGB32 );
    d->scene->setSceneRect( 0, 0, width, height );
    d->root->setWidth( width );
    d->root->setHeight( height );
}

void QtQuickRenderer::deliverEvent(QEvent* event)
{
    QRect bounds = d->scene->sceneRect().toRect();
    int screenX = 0;
    int screenY = 0;

    // Convert the event and deliver it to the scene.
    switch( event->type() )
    {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseMove:
        {
            QMouseEvent* ev = static_cast<QMouseEvent*>( event );

            screenX = qRound( qBound( 0, ev->globalPos().x(), bounds.width() - 1 ) );
            screenY = qRound( qBound( 0, ev->globalPos().y(), bounds.height() - 1 ) );
            QPoint pressedPos = QPoint( screenX, screenY );

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
            e.setButtonDownScreenPos( ev->button(), pressedPos );
            e.setButtonDownScenePos( ev->button(), QPointF( pressedPos.x() + bounds.x(), pressedPos.y() + bounds.y() ) );
            e.setButtons( ev->buttons() );
            e.setButton( ev->button() );
            e.setModifiers( ev->modifiers() );
            e.setAccepted( false );
            QCoreApplication::sendEvent( d->scene, &e );
        }
        break;
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
            QCoreApplication::sendEvent( d->scene, &e );
        }
        break;

        case QEvent::Leave:
        case QEvent::Enter:
        case QEvent::MetaCall:
            //These events should not be resent to the scene, it will in fact cause issues if they try.
            break;

        default:
        {
            // Send the event directly without any conversion.
            // Typically used for keyboard, focus, and enter/leave events.
            QCoreApplication::sendEvent( d->scene, event );
        }
        break;

    }
}

void QtQuickRenderer::Private::createEngine()
{
    engine = new QDeclarativeEngine( QCoreApplication::instance() );

    engine->rootContext()->setContextProperty( "MessageHandler", GluonCore::MessageHandler::instance() );
    engine->rootContext()->setContextProperty( "ObjectFactory", GluonCore::GluonObjectFactory::instance() );
}

 
