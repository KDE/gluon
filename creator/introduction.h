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
#include <KDE/KStandardDirs>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeItem>
#include <QtDeclarative/QDeclarativeView>
#include <QString>

class QDeclarativeContext;
class QDeclarativeItem;
class QDeclarativeView;
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
        QString dockername() const {return docker;}
        int width() const { return m_width; }
        int height() const { return m_height; }
        int xpos() const { return m_xpos; }
        int ypos() const { return m_ypos; }
        void setWidth(int width){ m_width=width;}
        void setHeight(int height){ m_height=height;}
        void setXpos(int xpos){ m_xpos=xpos;}
        void setYpos(int ypos){ m_ypos=ypos;}

        void setdockername(QString name){

            docker=name;
            if(docker!="") { updateDocker(); }
        }

        void startIntro();
        void updateDocker();

        GluonCreator::MainWindow *windowcopy;
        QDeclarativeView* view;
        QDeclarativeContext *context;
        QString docker;

    signals:

        void dockernameChanged();
        void widthChanged();
        void heightChanged();
        void xposChanged();
        void yposChanged();

    private:

        int m_width;
        int m_height;
        int m_xpos;
        int m_ypos;

};

#endif // IntroSlideShow_H
