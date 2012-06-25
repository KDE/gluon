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
#include "graphics/manager.h"
#include "graphics/renderwidget.h"

#include <QtGui/QApplication>
#include <shader.h>
#include <backend.h>
#include <texture.h>
#include <core/directoryprovider.h>

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    //GluonGraphics::RenderWidget widget;
    //widget.show();

    //GluonGraphics::Material* mat = new GluonGraphics::Material();
    //GluonGraphics::Material* mat = GluonGraphics::Manager::instance()->createResource< GluonGraphics::Material >( "Main" );
    //createResource< GluonGraphics::Material >( "Main" );
    //GluonGraphics::Manager::instance()->destroyResource< GluonGraphics::Material >( "Main" );
    //qDebug() << GluonGraphics::Manager::instance()->backend( widget )->information( GluonGraphics::Backend::VerboseInformation );
    GluonGraphics::RenderWidget widget;
    widget.show();
    //app.exec();

    GluonGraphics::Texture* texture = GluonGraphics::Manager::instance()->createResource< GluonGraphics::Texture >( "test" );
    texture->load( GluonCore::DirectoryProvider::instance()->dataDirectory() + "/gluon/defaults/default.png" );

    //delete widget;

    //Create a widget to render the graphics on.
//     GluonGraphics::RenderWidget* widget = new GluonGraphics::RenderWidget();
//     widget->show();

//     GluonGraphics::World* world = GluonGraphics::Manager::instance()->createWorld();

    //Create a camera to view the scene from.
//     GluonGraphics::Camera* cam = world->createEntity< GluonGraphics::Camera* >();

    //Set the viewport
//     cam->frustrum()->setOrthographic( -5.f, 5.f, -5.f, 5.f, -5.f, 5.f );

    //Activate the new camera
    //GluonGraphics::Manager::instance()->setActiveCamera( cam );

    //Create an item to display
//     GluonGraphics::Item* item = GluonGraphics::Engine::instance()->createItem( "default" );
//
//     QMatrix4x4 mat;
//     mat.translate( -1.5f, -1.5f );
//     item->setTransform( mat );
//
//     item = GluonGraphics::Engine::instance()->createItem( "default" );
//     mat.translate( 3.f, 3.f );
//     item->setTransform( mat );
//
//     QTimer::singleShot( 0, widget, SLOT(updateGL()) );
// return app.exec();

    app.exec();
}
