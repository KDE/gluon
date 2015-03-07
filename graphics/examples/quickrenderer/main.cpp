/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2015 Felix Rohrbach <kde@fxrh.de>
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

#include "graphics/material.h"

#include <QtCore/QSizeF>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QApplication>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <core/directoryprovider.h>
#include <core/resourcemanager.h>
#include <graphics/renderwindow.h>
#include <graphics/shader.h>
#include <graphics/backend.h>
#include <graphics/texture.h>
#include <graphics/world.h>
#include <graphics/entity.h>
#include <graphics/camera.h>
#include <graphics/spritemesh.h>
#include <graphics/materialinstance.h>
#include <graphics/rendertarget.h>
#include <graphics/frustum.h>
#include <graphics/defaults.h>
#include <graphics/qtquickrenderer.h>

using namespace GluonGraphics;

class ExampleRenderWindow: public RenderWindow
{
    public:
        ExampleRenderWindow() : p(0) {}

        void deliverEventsTo( QtQuickRenderer* renderer ) { p = renderer; }

    protected:
        void mousePressEvent( QMouseEvent* event ) { deliverEvent(event); }
        void mouseReleaseEvent( QMouseEvent* event ) { deliverEvent(event); }
        void wheelEvent( QWheelEvent* event ) { deliverEvent(event); }

    private:
        QtQuickRenderer* p;

        void deliverEvent( QEvent* event );
};

void ExampleRenderWindow::deliverEvent(QEvent* event)
{
    if( p )
    {
        p->deliverEvent( event );
        event->accept();
        update();
    }
}

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    ExampleRenderWindow window;
    window.show();

    Defaults::initialize();

    World* world = GluonCore::ResourceManager::instance()->resource< World >( Defaults::World );

    QtQuickRenderer* quickRenderer = Backend::currentBackend()->createQuickRenderer();
    DEBUG() << quickRenderer;
    quickRenderer->load( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/examples/graphics/example.qml" );

    window.deliverEventsTo( quickRenderer );

    Camera* cam = world->createEntity< Camera >();

    Eigen::Affine3f mat = Eigen::Affine3f::Identity();
    mat.translate( Eigen::Vector3f(0, 0, 50) );

    cam->setTransform( mat );
    cam->setVisibleArea( QSizeF( 20.f, 20.f ) );
    cam->setNearPlane( -100.f );
    cam->setFarPlane( 100.f );

    GluonCore::ResourceManager::instance()->resource< RenderTarget >( Defaults::RenderTarget )->addChild( quickRenderer );
    GluonCore::ResourceManager::instance()->resource< RenderTarget >( Defaults::RenderTarget )->addChild( cam );

    app.exec();
}
