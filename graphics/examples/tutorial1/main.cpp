/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (C) 2010 Arjen Hiemstra <>
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
#include <gluon/graphics/glwidget.h>
#include <gluon/graphics/engine.h>
#include <gluon/graphics/camera.h>
#include <gluon/graphics/item.h>
#include <gluon/graphics/meshes/polygonmesh.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //Create an Engine. This class contains all items that will be shown in the view.
    // to add item, call : addItem(KGLItem *) or addItems(KGLItemList *)
//    GluonGraphics::Engine * engine = new GluonGraphics::Engine;

    //this is the view widget . It's a QGLWidget child. Call KGLView::setEngine(KGLEngine *) to attach the engine to the view.
    // YOu can set the engine directly from the constructor
    GluonGraphics::GLWidget * view = new GluonGraphics::GLWidget();

    GluonGraphics::Camera* cam = new GluonGraphics::Camera();
    GluonGraphics::Engine::instance()->setActiveCamera(cam);

    GluonGraphics::PolygonMesh * mesh = new GluonGraphics::PolygonMesh(QRectF(0, 0, 5, 5));
    GluonGraphics::Item * item = new GluonGraphics::Item(mesh);


    item->setRotation(45);
    item->setColor(Qt::green);
    item->updateTransform();

    view->show();

    return app.exec();

}
