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

#include "graphics/renderwindow.h"

#include <cmath>

#include <QtGui/QGuiApplication>

#include "core/directoryprovider.h"
#include "core/resourcemanager.h"
#include "graphics/defaults.h"
#include "graphics/camera.h"
#include "graphics/frustum.h"
#include "graphics/filemesh.h"
#include "graphics/entity.h"
#include "graphics/world.h"
#include "graphics/material.h"
#include "graphics/materialinstance.h"
#include "graphics/texture.h"
#include "graphics/rendertarget.h"
#include "graphics/mathutils.h"

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace GluonGraphics;

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    RenderWindow window;
    window.show();

    Defaults::initialize();

    Eigen::Affine3f mat = Eigen::Affine3f::Identity();

    FileMesh* mesh = new FileMesh( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/examples/graphics/duck.dae" );
    GluonCore::ResourceManager::instance()->addResource< Mesh >( "duck.dae", mesh );
    mesh->initialize();
    Texture* texture = GluonCore::ResourceManager::instance()->createResource< Texture >( "duck.tga" );
    texture->load( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/examples/graphics/duck.tga" );

    Material* material = GluonCore::ResourceManager::instance()->createResource< Material>( "duck" );
    material->load( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/examples/graphics/duck.gluonmaterial" );
    material->build();

    World* world = GluonCore::ResourceManager::instance()->resource< World >( Defaults::World );

    Entity* ent = world->createEntity< Entity >();
    mat.rotate( Eigen::AngleAxis<float>( -M_PI_4 /* pi/4 */, Eigen::Vector3f(0.f, 1.f, 0.f) ) );
    ent->setTransform( mat );
    ent->setMesh( mesh );
    ent->setMaterialInstance( material->createInstance() );
    ent->materialInstance()->setProperty( "texture0", QVariant::fromValue( texture ) );

    Camera* cam = world->createEntity< Camera >();
    mat = Eigen::Affine3f::Identity();
    mat.translate( Eigen::Vector3f(0.f, 75.f, 100.f) );
    cam->setTransform( mat );

    cam->setVisibleArea( QSizeF( 200.f, 200.f ) );
    cam->setNearPlane( 0.f );
    cam->setFarPlane( 1000.f );

    GluonCore::ResourceManager::instance()->resource< RenderTarget >( Defaults::RenderTarget )->addChild( cam );

    //app.exec();

    return app.exec();
}
