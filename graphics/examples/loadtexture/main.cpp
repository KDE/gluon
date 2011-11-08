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
#include "graphics/rendertarget.h"
#include "graphics/engine.h"
#include "graphics/camera.h"
#include "graphics/item.h"
#include "graphics/frustrum.h"
#include "graphics/texture.h"
#include "graphics/material.h"
#include "graphics/materialinstance.h"
#include "graphics/abstractmesh.h"

#include <core/directoryprovider.h>

#include <QtGui/QApplication>
#include <QtGui/QMatrix4x4>
#include <QtCore/QTimer>

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    //Store the engine instance in a variable
    GluonGraphics::Engine *engine = GluonGraphics::Engine::instance();

    //Create a widget to render the graphics on.
    GluonGraphics::RenderWidget* widget = new GluonGraphics::RenderWidget();
    widget->show();

    //Create a camera to view the scene from.
    GluonGraphics::Camera* cam = new GluonGraphics::Camera();

    //Set the viewport
    cam->frustrum()->setOrthographic( -5.f, 5.f, -5.f, 5.f, -5.f, 5.f );

    //Activate the new camera
    engine->setActiveCamera( cam );

    //Create a material
    GluonGraphics::Material* material = engine->createMaterial( "customMaterialName" );
    material->load( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/defaults/default.gml" );
    material->build();

    //Create an instance for the material
    GluonGraphics::MaterialInstance *materialInstance = engine->material("customMaterialName")->createInstance("InstanceName");

    //Create an item to display
    GluonGraphics::Item* item = engine->createItem( "default" );
    item->setMaterialInstance(materialInstance);

    //Load a custom texture from file
    GluonGraphics::Texture* texture = engine->createTexture( "TextureName" );
    texture->load( QUrl( GluonCore::DirectoryProvider::instance()->dataDirectory()
                    + "/gluon/games/ball.gluon/assets/textures/ball.png" ) );
    item->materialInstance()->setProperty( "texture0", "TextureName" );

    //Create another instance for the material
    GluonGraphics::MaterialInstance *materialInstance2 = engine->material("customMaterialName")->createInstance("Instance2Name");

    //Create another item to display
    GluonGraphics::Item* item2 = engine->createItem( "default" );
    item2->setMaterialInstance(materialInstance2);

    //Load another custom texture from file
    GluonGraphics::Texture* texture2 = engine->createTexture( "Texture2Name" );
    texture2->load( QUrl( GluonCore::DirectoryProvider::instance()->dataDirectory()
                     + "/gluon/games/ball.gluon/assets/textures/trap.png" ));
    item2->materialInstance()->setProperty( "texture0", "Texture2Name" );

    QMatrix4x4 mat;
    mat.translate( 1.5f, 1.5f );
    item->setTransform( mat );

    QMatrix4x4 mat2;
    mat2.translate( -1.5f, -1.5f );
    item2->setTransform( mat2 );

    QTimer::singleShot( 0, widget, SLOT(updateGL()) );
    return app.exec();
}
