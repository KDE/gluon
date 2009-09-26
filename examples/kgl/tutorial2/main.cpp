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
#include <QWidget>
#include <gluon/kgl/kglview.h>
#include <gluon/kgl/kglengine.h>
#include <gluon/kgl/kglboxitem.h>
#include <gluon/kgl/kglparticlesitem.h>
using namespace std;



int main(int argc, char *argv[])
{
    KAboutData aboutData("kgl_tutorial2", 0,
                         ki18n("gluon"), "1.0",
                         ki18n("gluon"),
                         KAboutData::License_GPL,
                         ki18n("Copyright (c) 2009 Developer"));
    KCmdLineArgs::init(argc, argv, &aboutData);

    KApplication app;


    KGLEngine * engine = new KGLEngine; 
    KGLView * view = new KGLView(engine);

    KGLParticlesItem * explose = new KGLParticlesItem;
    explose->createSmoke(40,KIcon("kgl").pixmap(32,32),45,0.07,0.003,32);
    engine->addItem(explose);
    explose->setPosition(-10,-10);
    explose->setAngle(0);
    explose->updateTransform();


    KGLParticlesItem * explose2 = new KGLParticlesItem;
    explose2->createSmoke(40,KIcon("kal").pixmap(32,32),45,0.07,0.003,32);
    engine->addItem(explose2);
    explose2->setAngle(180);
    explose2->setPosition(10,10);
    explose2->updateTransform();


    KGLParticlesItem * gluon = new KGLParticlesItem;
    gluon->createExplose(40,KIcon("gluon").pixmap(32,32),360,0.1,0.01,25);
    engine->addItem(gluon);


    view->start(); 
    view->show();
    app.exec();

}
