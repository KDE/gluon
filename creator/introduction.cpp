/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Shreya Pandit <shreya@shreyapandit.com>
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

#include "introduction.h"
#include <QRect>
#include <QDebug>
#include <KDE/KApplication>

class QRect;
class QDebug;
class KApplication;

IntroSlideShow::IntroSlideShow()
{
    qDebug() << "INSIDE CONSTRUCTOR";
    timer = new QTimer();
    timer->setSingleShot(true);
    timer->singleShot(3000, this, SLOT(on_timeout()));
}

IntroSlideShow::~IntroSlideShow()
{
    delete timer;
}

void IntroSlideShow::startIntro()
{
    qDebug() << "INSIDE START INTRO";

/*    view = new QDeclarativeView( QUrl::fromLocalFile( KGlobal::dirs()->locate( "appdata", "introduction.qml" ) ), this_windowcopy );
    view->setStyleSheet("background: transparent");
    view->setResizeMode( QDeclarativeView::SizeRootObjectToView );
    view->setGeometry(this_windowcopy->rect());
    view->show();*/

}

void IntroSlideShow::on_timeout()
{
    qDebug() << "INSIDE TIMEOUT";
    this_windowcopy= kapp->activeWindow();
    qDebug() <<"OUR WINDOWCOPY IS" << this_windowcopy;
    qmlRegisterType<IntroSlideShow>("Intro",1,0,"IntroSlideShow");

}



void IntroSlideShow::updateDocker()
{
    qDebug() << "Inside updateDocker";
    QWidget *rectangle;

    /*setWidth(rectangle->width());
    setHeight(rectangle->height());
    setXpos(rectangle->x());
    setYpos(rectangle->y());
*/

}

