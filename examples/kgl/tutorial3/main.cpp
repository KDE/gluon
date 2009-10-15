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

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KDebug>
#include <KIcon>
#include <QWidget>
#include <gluon/kgl/kglview.h>
#include <gluon/kgl/kglengine.h>
#include <gluon/kgl/kglboxitem.h>
#include <gluon/kgl/kglphysicsitem.h>
#include <gluon/kgl/kglphysicsengine.h>
#include <gluon/kgl/kglboxitem.h>
#include <gluon/kgl/kgldebugphysicsview.h>

using namespace std;



int main(int argc, char *argv[])
{
    KAboutData aboutData("kgl_tutorial3", 0,
                         ki18n("gluon"), "1.0",
                         ki18n("gluon"),
                         KAboutData::License_GPL,
                         ki18n("Copyright (c) 2009 Developer"));
    KCmdLineArgs::init(argc, argv, &aboutData);

    KApplication app;

    KGLPhysicsEngine * engine = new KGLPhysicsEngine;
    KGLDebugPhysicsView * view = new KGLDebugPhysicsView();
    view->setEngine(engine);


  
    
    KGLPhysicsItem * ground = new KGLPhysicsItem;
    ground->setStatic();
    ground->createBox(20,2);
    ground->setPosition(-10,-10);
    ground->updateTransform();
    engine->addItem(ground);
    

    KGLPhysicsItem * pendule= new KGLPhysicsItem(NULL, KGLPhysicsItem::PolygonShape);
    pendule->createBox(3,3);
    pendule->setPosition(-5,0);
    pendule->updateTransform();
    pendule->setTexture(KIcon("kde.png").pixmap(256,256));
    pendule->setRestitution(0.4);
    engine->addItem(pendule);

    KGLPhysicsItem * pendule2= new KGLPhysicsItem(NULL, KGLPhysicsItem::PolygonShape );
    pendule2->createBox(3,3);
    pendule2->setPosition(0,0);
    pendule2->updateTransform();
    pendule2->setTexture(KIcon("kde.png").pixmap(256,256));
    pendule2->setRestitution(0.7);
    engine->addItem(pendule2);

      engine->world()->SetDebugDraw(view);
    view->start();
    view->show();
    app.exec();

}
