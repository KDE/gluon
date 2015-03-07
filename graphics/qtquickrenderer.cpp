/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "qtquickrenderer.h"

#include <QQmlComponent>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickRenderControl>
#include <QQuickWindow>
#include <QQuickItem>

#include "spritemesh.h"
#include "materialinstance.h"
#include "mathutils.h"
#include "defaults.h"
#include "material.h"

#include <core/resourcemanager.h>
#include <core/messagehandler.h>
#include <core/log.h>
#include <core/gluonvarianttypes.h>

using namespace GluonGraphics;

class QtQuickRenderer::Private
{
    public:
        Private(): width(1024), height(1024), quickLoaded(false), quickInitialized(false), needsUpdating(false){}

        void createEngine();

        QQuickRenderControl* renderControl;
        QQuickWindow* quickWindow;
        static QQmlEngine* qmlEngine;
        QQmlComponent* qmlComponent;
        QQuickItem* rootItem;
        QQmlContext* context;

        int width;
        int height;

        bool quickLoaded;
        bool quickInitialized;
        bool needsUpdating;

        SpriteMesh* mesh;
        MaterialInstance* material;
};

QQmlEngine* QtQuickRenderer::Private::qmlEngine = 0;

void QtQuickRenderer::Private::createEngine()
{
    qmlEngine = new QQmlEngine( QCoreApplication::instance() );
    if( !qmlEngine->incubationController() )
        qmlEngine->setIncubationController( quickWindow->incubationController() );

    qmlEngine->rootContext()->setContextProperty( "MessageHandler", GluonCore::MessageHandler::instance() );
    qmlEngine->rootContext()->setContextProperty( "ObjectFactory", GluonCore::GluonObjectFactory::instance() );
}

QtQuickRenderer::QtQuickRenderer( QObject* parent )
    : Texture(parent)
    , d(new Private())
{
        //TODO: Make this configurable
    setZDepth( -1.0f );

    d->mesh = GluonCore::ResourceManager::instance()->resource< GluonGraphics::SpriteMesh >( GluonGraphics::Defaults::SpriteMesh );
    d->material = GluonCore::ResourceManager::instance()->resource< GluonGraphics::Material >( GluonGraphics::Defaults::Material )->createInstance();
    Eigen::Affine3f proj = MathUtils::ortho( -0.5, 0.5, -0.5, 0.5, -2, 2);
    d->material->setProperty( "projectionMatrix", QVariant::fromValue(proj) );
    Eigen::Affine3f id = Eigen::Affine3f::Identity();
    d->material->setProperty( "viewMatrix", QVariant::fromValue(id) );
    d->material->setProperty( "modelMatrix", QVariant::fromValue(id) );
    d->material->setProperty( "texture0", QVariant::fromValue< Texture* >( this ) );

    d->renderControl = new QQuickRenderControl(this);
    d->quickWindow = new QQuickWindow(d->renderControl);

    connect( d->renderControl, &QQuickRenderControl::sceneChanged, this, &QtQuickRenderer::requestUpdate );

    if( !d->qmlEngine )
        d->createEngine();
}

QtQuickRenderer::~QtQuickRenderer()
{
    delete d;
}

void QtQuickRenderer::renderContents()
{
    if( d->needsUpdating )
    {
        if( !d->quickLoaded )
        {
            if( d->qmlComponent->isLoading() )
            {
                connect( d->qmlComponent, &QQmlComponent::statusChanged, this, &QtQuickRenderer::startQuick );
                return;
            }
            else
            {
                startQuick();
            }
        }

        renderQuick();
    }

    d->material->bind();
    d->mesh->render( d->material->shader() );
    d->material->release();
}

void QtQuickRenderer::load( const QUrl& url )
{
    d->quickInitialized = false;
    d->needsUpdating = false;

    d->qmlComponent = new QQmlComponent( d->qmlEngine, url );
}

QImage QtQuickRenderer::image() const
{
    // TODO: This might need the right context to be active
    DEBUG();
    QImage img = d->renderControl->grab();
    return img;
}

QQmlContext* QtQuickRenderer::context() const
{
    return d->context;
}

void QtQuickRenderer::resize(int width, int height)
{
    DEBUG() << width << "x" << height;
    d->width = width;
    d->height = height;

    if( d->quickLoaded )
    {
        d->rootItem->setWidth( d->width );
        d->rootItem->setHeight( d->height );
    }

    d->quickWindow->setGeometry( 0, 0, width, height );
    d->needsUpdating = true;
}

void QtQuickRenderer::deliverEvent(QEvent* event)
{
    // Convert the event and deliver it to the scene.
    switch( event->type() )
    {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseMove:
        {
            QMouseEvent* ev = static_cast<QMouseEvent*>( event );

            // From the rendercontrol example:
            // "Use the constructor taking localPos and screenPos. That puts localPos into the
            // event's localPos and windowPos, and screenPos into the event's screenPos. This way
            // the windowPos in e is ignored and is replaced by localPos. This is necessary
            // because QQuickWindow thinks of itself as a top-level window always."

            QMouseEvent mappedEvent( ev->type(), ev->localPos(), ev->screenPos(), ev->button(), ev->buttons(), ev->modifiers() );
            QCoreApplication::sendEvent( d->quickWindow, &mappedEvent );
        }
        break;
        case QEvent::Wheel:
        {
            QWheelEvent* ev = static_cast<QWheelEvent*>( event );
            QWheelEvent mappedEvent( ev->posF(), ev->globalPosF(), ev->pixelDelta(), ev->angleDelta(), ev->delta(), ev->orientation(), ev->buttons(), ev->modifiers(), ev->phase() );
            QCoreApplication::sendEvent( d->quickWindow, &mappedEvent );
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
            QCoreApplication::sendEvent( d->quickWindow, event );
        }
        break;

    }
}

void QtQuickRenderer::requestUpdate()
{
    d->needsUpdating = true;
}

int QtQuickRenderer::width()
{
    return d->width;
}

int QtQuickRenderer::height()
{
    return d->height;
}

QQuickWindow* QtQuickRenderer::quickWindow()
{
    return d->quickWindow;
}

QQuickRenderControl* QtQuickRenderer::renderControl()
{
    return d->renderControl;
}

bool QtQuickRenderer::quickLoaded()
{
    return d->quickLoaded;
}

bool QtQuickRenderer::quickInitialized()
{
    return d->quickInitialized;
}

bool QtQuickRenderer::needsUpdating()
{
    return d->needsUpdating;
}

bool QtQuickRenderer::startQuick()
{
    disconnect( d->qmlComponent, &QQmlComponent::statusChanged, this, &QtQuickRenderer::startQuick );

    if( d->qmlComponent->isError() )
    {
        QList<QQmlError> errorList = d->qmlComponent->errors();
        for( const QQmlError& error: errorList )
        {
            ERROR() << error.url().toDisplayString() << error.line() << error.toString();
        }
        return false;
    }

    QObject* rootObject = d->qmlComponent->create();
    if( d->qmlComponent->isError() )
    {
        QList<QQmlError> errorList = d->qmlComponent->errors();
        for( const QQmlError& error: errorList )
        {
            ERROR() << error.url().toDisplayString() << error.line() << error.toString();
        }
        return false;
    }

    d->rootItem = qobject_cast<QQuickItem*>(rootObject);
    if( !d->rootItem )
    {
        ERROR() << "Not a QQuickItem!";
        delete rootObject;
        return false;
    }

    d->rootItem->setWidth(width());
    d->rootItem->setHeight(height());

    d->rootItem->setParentItem( d->quickWindow->contentItem() );

    d->context = new QQmlContext( d->qmlEngine->rootContext(), this );

    d->quickLoaded = true;
    d->quickInitialized = false;
    d->needsUpdating = true;
    return true;
}


