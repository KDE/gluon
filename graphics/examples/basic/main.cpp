/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "graphics/material.h"

#include <QtCore/QSizeF>
#include <QtGui/QGuiApplication>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <core/directoryprovider.h>
#include <graphics/manager.h>
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
#include <graphics/frustrum.h>

using namespace GluonGraphics;

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    RenderWindow window;
    window.show();

    Manager::instance()->initialize();

    Entity* ent = Manager::instance()->currentWorld()->createEntity< Entity >();
    ent->setMesh( Manager::instance()->resource< SpriteMesh >( Manager::Defaults::SpriteMesh ) );
    ent->setMaterialInstance( Manager::instance()->resource< Material >( Manager::Defaults::Material )->createInstance() );
    ent->materialInstance()->setProperty( "texture0", QVariant::fromValue( Manager::instance()->resource< Texture >( Manager::Defaults::Texture ) ) );

    Camera* cam = Manager::instance()->currentWorld()->createEntity< Camera >();

    Eigen::Affine3f mat = Eigen::Affine3f::Identity();
    mat.translate( Eigen::Vector3f(0, 0, 50) );

    cam->setTransform( mat );
    cam->setVisibleArea( QSizeF( 20.f, 20.f ) );
    cam->setNearPlane( -100.f );
    cam->setFarPlane( 100.f );

    Manager::instance()->resource< RenderTarget >( Manager::Defaults::RenderTarget )->addChild( cam );

    app.exec();
}
