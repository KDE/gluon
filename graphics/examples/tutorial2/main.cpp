/*
* This file is part of the KGLEngine2D project.
* Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
* Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
* Copyright (C) 2008 Charles Huet <packadal@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; see the file COPYING.  If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301, USA.
*/







#include <QApplication>

#include <QDebug>
#include <QTimer>
#include <gluon/graphics/glwidget.h>
#include <gluon/graphics/engine.h>
#include <gluon/graphics/item.h>
#include <gluon/graphics/camera.h>
#include "testa.h"


using namespace GluonGraphics;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    //Create the openGL View
    GluonGraphics::GLWidget * view = new GluonGraphics::GLWidget();

    //Create a camera
    GluonGraphics::Camera *cam = new GluonGraphics::Camera();
    GluonGraphics::Engine::instance()->setActiveCamera(cam);

    //Use a timer to update frame each 20 ms
    QTimer * timer = new QTimer;
    timer->start(20);
    QObject::connect(timer, SIGNAL(timeout()), view, SLOT(updateGL()));


//this class add a cube and move it
    Testa * test = new Testa;
    QObject::connect(timer, SIGNAL(timeout()), test, SLOT(test()));



    view->show();

    return app.exec();

}
