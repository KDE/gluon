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

#include <QApplication>
#include <QMatrix4x4>

#include "core/directoryprovider.h"
#include "graphics/manager.h"
#include "graphics/camera.h"
#include "graphics/frustrum.h"
#include "graphics/filemesh.h"
#include "graphics/entity.h"
#include "graphics/world.h"
#include "graphics/material.h"
#include "graphics/materialinstance.h"
#include "graphics/texture.h"
#include "graphics/rendertarget.h"
#include <mathutils.h>

using namespace GluonGraphics;

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    RenderWidget widget;
    widget.show();

    Manager::instance()->initialize();

    QMatrix4x4 mat;

    FileMesh* mesh = new FileMesh( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/examples/graphics/duck.dae" );
    Manager::instance()->addResource< Mesh >( "duck.dae", mesh );
    mesh->initialize();
    Texture* texture = Manager::instance()->createResource< Texture >( "duck.tga" );
    texture->load( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/examples/graphics/duck.tga" );

    Material* material = Manager::instance()->createResource< Material>( "duck" );
    material->load( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/examples/graphics/duck.gluonmaterial" );
    material->build();


    Entity* ent = Manager::instance()->currentWorld()->createEntity< Entity >();
    mat.rotate( 45, MathUtils::VECTOR_UNIT_Y );
    ent->setTransform( mat );
    ent->setMesh( mesh );
    ent->setMaterialInstance( material->createInstance() );
    //ent->materialInstance()->setProperty( "texture0", QVariant::fromValue( texture ) );

    Camera* cam = Manager::instance()->currentWorld()->createEntity< Camera >();
    mat.setToIdentity();
    mat.translate( 0, -75.f, -500.f );
    cam->setTransform( mat );

    cam->setVisibleArea( QSizeF( 200.f, 200.f ) );
    cam->setNearPlane( 0.f );
    cam->setFarPlane( 1000.f );

    Manager::instance()->resource< RenderTarget >( Manager::Defaults::RenderTarget )->addChild( cam );

    //app.exec();

    return app.exec();
}
