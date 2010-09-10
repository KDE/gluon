/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
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

#include <QApplication>
#include <QtGui/QMatrix4x4>

#include <gluon/graphics/renderwidget.h>
#include <gluon/graphics/engine.h>
#include <gluon/graphics/camera.h>
#include <gluon/graphics/item.h>
#include <gluon/graphics/frustum.h>
#include <gluon/graphics/material.h>
#include <gluon/graphics/mesh.h>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Create a widget to render the graphics on.
    GluonGraphics::RenderWidget * widget = new GluonGraphics::RenderWidget();
    widget->show();

    //Create a camera to view the scene from.
    GluonGraphics::Camera* cam = new GluonGraphics::Camera();

    //Set the viewport
    cam->frustum()->setOrthographic(-5.f, 5.f, -5.f, 5.f, -5.f, 5.f);

    //Activate the new camera
    GluonGraphics::Engine::instance()->setActiveCamera(cam);

    //Create an item to display
    GluonGraphics::Item * item = GluonGraphics::Engine::instance()->createItem("default");
    QMatrix4x4 mat;
    mat.translate(-1.5f, 0.f);
    item->setTransform(mat);
    item->mesh()->load(QString());
    GluonGraphics::Material * material = GluonGraphics::Engine::instance()->createMaterial("default");
    material->build();
    item->mesh()->setMaterial(material->createInstance());

    item = GluonGraphics::Engine::instance()->createItem("default");
    mat.translate(3.0f, 0.f);
    item->setTransform(mat);

    QTimer timer;
    timer.setInterval(0);
    QObject::connect(&timer, SIGNAL(timeout()), widget, SLOT(updateGL()));
    timer.start();

    return app.exec();

}
