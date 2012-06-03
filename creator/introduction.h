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

#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include "mainwindow.h"
#include <QtDeclarative/QDeclarativeItem>
#include <QString>

class QDeclarativeItem;
class QString;


class IntroSlideShow: public QDeclarativeItem
{
        Q_OBJECT
        Q_PROPERTY(QString dockername READ dockername WRITE setdockername NOTIFY dockernameChanged)
        Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
        Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
        Q_PROPERTY(int xpos READ xpos WRITE setXpos NOTIFY xposChanged)
        Q_PROPERTY(int ypos READ ypos WRITE setYpos NOTIFY yposChanged)

        public:
            IntroSlideShow();
            ~IntroSlideShow();
            QString dockername() const {return docker;}
            qreal width() const { return implicitWidth(); }
            qreal height() const { return implicitHeight(); }
            int xpos() const { return x(); }
            int ypos() const { return y(); }
            void setWidth(qreal width);
            void setHeight(qreal height);
            void setXpos(qreal xpos);
            void setYpos(qreal ypos);
            Q_INVOKABLE void setdockername(QString name);
            void updateDocker();
            QString docker;

        signals:

            void dockernameChanged();
            void widthChanged();
            void heightChanged();
            void xposChanged();
            void yposChanged();


};

#endif // IntroSlideShow_H
