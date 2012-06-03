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
#include <KDE/KApplication>

class QRect;
class KApplication;

IntroSlideShow::IntroSlideShow()
{

}

IntroSlideShow::~IntroSlideShow()
{
    delete this;
}

void IntroSlideShow::setWidth(qreal width)
{
    setImplicitWidth(width);
    emit widthChanged();
}


void IntroSlideShow::setHeight(qreal height)
{
    setImplicitHeight(height);
    emit heightChanged();
}

void IntroSlideShow::setXpos(qreal xpos)
{
    setX(xpos);
    emit xposChanged();
}

void IntroSlideShow::setYpos(qreal ypos)
{
    setY(ypos);
    emit yposChanged();
}

void IntroSlideShow::setdockername(QString name)
{
    docker=name;
    if(QString::compare(docker,"", Qt::CaseInsensitive)) {
        updateDocker();
   }

    emit dockernameChanged();
}

void IntroSlideShow::updateDocker()
{
    QRect rectangle;
    rectangle= kapp->activeWindow()->findChild<QWidget*>(docker)->frameGeometry();
    setWidth(rectangle.width());
    setHeight(rectangle.height());
    setXpos(rectangle.x());
    setYpos(rectangle.y());

}

