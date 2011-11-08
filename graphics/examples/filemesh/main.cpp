/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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
#include "graphics/material.h"
#include "graphics/materialinstance.h"
#include "graphics/filemesh.h"
#include "graphics/texture.h"

#include <QtGui/QMatrix4x4>
#include <QtGui/QApplication>
#include <QtCore/QTimer>
#include <core/directoryprovider.h>

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    //Create a widget to render the graphics on.
    GluonGraphics::RenderWidget* widget = new GluonGraphics::RenderWidget();
    widget->show();

    //Create a camera to view the scene from.
    GluonGraphics::Camera* cam = new GluonGraphics::Camera();

    //Set the viewport
    cam->frustrum()->setOrthographic( -110.f, 110.f, -110.f, 110.f, -110.f, 110.f );

    //Activate the new camera
    GluonGraphics::Engine::instance()->setActiveCamera( cam );

    //Create a new FileMesh to load vertex data from a mesh.
    GluonGraphics::FileMesh* mesh = new GluonGraphics::FileMesh(GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/examples/graphics/duck.dae" );
    //Load the data.
    mesh->initialize();
    //Register it with the Engine so we can track it.
    GluonGraphics::Engine::instance()->addMesh("duck", mesh);

    //Load the texture of the mesh.
    GluonGraphics::Texture* tex = GluonGraphics::Engine::instance()->createTexture( "duck" );
    tex->load( QUrl( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/examples/graphics/duck.tga" ) );

    //Create an item to display
    GluonGraphics::Item* item = GluonGraphics::Engine::instance()->createItem( "duck" );

    //Apply the texture to the item.
    item->materialInstance()->setProperty( "texture0", "duck" );

    QMatrix4x4 matrix;
    matrix.translate(0.f, -75.f, 0.f);
    matrix.rotate(-45.f, 0.f, 1.f, 0.f);
    item->setTransform(matrix);

    QTimer::singleShot( 0, widget, SLOT(updateGL()) );
    return app.exec();
}
