/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
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

#include "graphics/renderwidget.h"
#include "graphics/engine.h"
#include "graphics/camera.h"
#include "graphics/item.h"
#include "graphics/frustrum.h"
#include "graphics/texture.h"
#include "graphics/material.h"
#include "graphics/materialinstance.h"
#include "graphics/mesh.h"

#include <core/directoryprovider.h>

#include <QtGui/QApplication>
#include <QtGui/QMatrix4x4>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    //Create a widget to render the graphics on.
    GluonGraphics::RenderWidget* widget = new GluonGraphics::RenderWidget();
    widget->show();

    //Create a camera to view the scene from.
    GluonGraphics::Camera* cam = new GluonGraphics::Camera();

    //Set the viewport
    cam->frustrum()->setOrthographic( -5.f, 5.f, -5.f, 5.f, -5.f, 5.f );

    //Activate the new camera
    GluonGraphics::Engine::instance()->setActiveCamera( cam );

    //Create an item to display
    GluonGraphics::Item* item = GluonGraphics::Engine::instance()->createItem( "default" );

    //Load a custom texture from file
    GluonGraphics::Texture* tex = GluonGraphics::Engine::instance()->createTexture( "textureName" );
    tex->load( QUrl( GluonCore::DirectoryProvider::dataDirectory() + "/gluon/defaults/default.png" ) );
    item->materialInstance()->setProperty( "texture0", "textureName" );

    QMatrix4x4 mat;
    mat.translate( -1.5f, -1.5f );
    item->setTransform( mat );

    QTimer::singleShot( 0, widget, SLOT( updateGL() ) );
    return app.exec();
}
