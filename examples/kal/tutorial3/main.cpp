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
#include <QDebug>
#include <gluon/kal/kalsound.h>
#include <gluon/kal/kalengine.h>
#include <gluon/kal/widgets/kalplayerwidget.h>

int main(int argc, char *argv[])
{
    KAboutData aboutData("kcl_tutorial3", 0,
                         ki18n("gluon"), "1.0",
                         ki18n("gluon"),
                         KAboutData::License_GPL,
                         ki18n("Copyright (c) 2009 Developer"));
    KCmdLineArgs::init(argc, argv, &aboutData);
KApplication app;



KALSound * left = new KALSound("/usr/share/sounds/alsa/Front_Left.wav");
KALSound * right = new KALSound("/usr/share/sounds/alsa/Front_Right.wav");
KALSound * center = new KALSound("/usr/share/sounds/alsa/Front_Center.wav");

left->setPosition(-1,0,0);
right->setPosition(1,0,0);

left->play();
while ( left->status() == AL_PLAYING){}

right->play();
while ( right->status() == AL_PLAYING){}

center->play();

   app.exec();
}
