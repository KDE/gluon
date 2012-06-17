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

#include "introslideshow.h"
#include <QRect>
#include <KDE/KApplication>
#include <QDebug>

class QDebug;
class QRect;
class KApplication;

IntroSlideShow::IntroSlideShow()
{

}

IntroSlideShow::~IntroSlideShow()
{
    delete this;
}

int IntroSlideShow::height() const
{
    return m_height;
}

int IntroSlideShow::width() const
{
    return m_width;
}

void IntroSlideShow::setWidth(qreal width)
{
    m_width = width;
    emit widthChanged();
}

void IntroSlideShow::setHeight(qreal height)
{
    m_height = height;
    emit heightChanged();
}
void IntroSlideShow::setDockername(QString name)
{

    docker=name;
    updateDocker();
    emit dockernameChanged();


}

qreal IntroSlideShow::getdockX()
{
    return dockX;
}

qreal IntroSlideShow::getdockWidth()
{
    return dockWidth;
}

QString IntroSlideShow::dockername() const
{
    return docker;
}

qreal IntroSlideShow::getrefWidth()
{
     return refWidth;
}

void IntroSlideShow::updateDocker()
{
    count++;
    QRect rectangle;
    rectangle= kapp->activeWindow()->findChild<QWidget*>(docker)->frameGeometry();
    setWidth(rectangle.width());
    refWidth=kapp->activeWindow()->width()/2 ;
    dockX= rectangle.x();
    dockWidth= rectangle.width();
    setHeight(rectangle.height());
    setX(rectangle.x());
    setY(rectangle.y());
    qDebug()<<rectangle.x()+rectangle.width();
    qDebug()<<kapp->activeWindow()->width()/2 ;
}

void IntroSlideShow::setX (int x)
{
    m_x = x;
    emit xChanged();
}

void IntroSlideShow::setY (int y)
{
    m_y = y;
    emit yChanged();
}

int IntroSlideShow::x() const
{
    return m_x;
}

int IntroSlideShow::y() const
{
    return m_y;
}
