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

class QRect;

IntroSlideShow::IntroSlideShow()
{
    qmlRegisterType<IntroSlideShow>("Intro",1,0,"IntroSlideshow");

}


void IntroSlideShow::startIntro()
{

    setdockername("");
    view->setSource( QUrl::fromLocalFile( KGlobal::dirs()->locate( "appdata", "introduction.qml" ) ));
    view->setStyleSheet("background: transparent");
    view->setResizeMode( QDeclarativeView::SizeRootObjectToView );
    view->setGeometry( windowcopy->rect());
    view->show();

}

void IntroSlideShow::updateDocker()
{
    QRect rectangle;
    rectangle= windowcopy->findChild<QWidget*>( docker )->frameGeometry();
    setWidth(rectangle.width());
    setHeight(rectangle.height());
    setXpos(rectangle.x());
    setYpos(rectangle.y());


}

