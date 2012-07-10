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
#include <QtGlobal>

class QDeclarativeItem;
class QString;

class IntroSlideShow: public QObject
{
        Q_OBJECT
        Q_PROPERTY(QString dockername READ dockername WRITE setDockername NOTIFY dockernameChanged)
        Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged )
        Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
        Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
        Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)

        public:
            IntroSlideShow();
            ~IntroSlideShow();
            QString dockername() const;
            int width() const;
            int height() const;
            //TODO: change to properties instead of INVOKABLEs
            Q_INVOKABLE qreal bLeftMain();
            Q_INVOKABLE qreal bLeftDock();
            Q_INVOKABLE qreal tRightDock();
            Q_INVOKABLE qreal tRightMain();
            Q_INVOKABLE qreal dWidth();
            Q_INVOKABLE qreal dHeight();
            Q_INVOKABLE qreal dX();
            Q_INVOKABLE qreal dY();
            Q_INVOKABLE qreal mX();
            Q_INVOKABLE qreal mY();
            void setWidth(qreal width);
            void setHeight(qreal height);
            void setDockername(QString name);
            void updateDocker();
            int x() const;
            void setX(int x);
            void setY(int y);
            int y() const;

        private:
            QString docker;
            qreal mainWidth;
            qreal mainX;
            qreal mainY;
            qreal mainHeight;
            qreal dockX;
            qreal dockWidth;
            qreal dockY;
            qreal dockHeight;
            int m_width;
            int m_height;
            int m_x;
            int m_y;

        public slots:
            void getWindow();

        signals:
            void dockernameChanged();
            void widthChanged();
            void heightChanged();
            void alignmentChanged();
            void xChanged();
            void yChanged();
};

#endif // IntroSlideShow_H
