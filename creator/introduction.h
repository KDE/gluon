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
#include <QtDeclarative/QDeclarativeView>
#include <QGraphicsObject>
#include <QString>
class QDeclarativeContext;
class QDeclarativeView;
class QString;

class IntroSlideShow: public QObject
{

    Q_OBJECT

    public:
        IntroSlideShow(QObject *parent = 0);

        Q_INVOKABLE void updateDocker(QString dockername);

        void startIntro();

        GluonCreator::MainWindow *windowcopy;
        QDeclarativeView* view;
        QDeclarativeContext *context;
        QString docker;
};

#endif // IntroSlideShow_H
