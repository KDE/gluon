/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2012 Shreya Pandit <shreya@shreyapandit.com>
 * Copyright (c) 2013 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#include "dockeroverlay.h"

#include <QtCore/QRect>
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

class DockerOverlay::Private
{
    public:
        Private( DockerOverlay* qq ) : q( qq ) { }
        void updateDocker();

        DockerOverlay* q;
        QString dockerName;
};

DockerOverlay::DockerOverlay( QQuickItem* parent )
    : QQuickItem( parent ), d( new Private( this ) )
{

}

DockerOverlay::~DockerOverlay()
{
    delete d;
}

QString DockerOverlay::dockerName() const
{
    return d->dockerName;
}

void DockerOverlay::setDockerName( const QString& name )
{
    if( name != d->dockerName )
    {
        d->dockerName = name;
        d->updateDocker();

        emit dockerNameChanged();
    }
}

void DockerOverlay::Private::updateDocker()
{
    QWidget* docker = qApp->activeWindow()->findChild<QWidget*>(dockerName);

    if( docker )
    {
        QRect dockerGeometry = docker->frameGeometry();

        q->setProperty("x", dockerGeometry.x());
        q->setProperty("y", dockerGeometry.y());
        q->setProperty("width", dockerGeometry.width());
        q->setProperty("height", dockerGeometry.height());
    }
    else
    {
        q->setProperty("x", q->parentItem()->width() / 2.f);
        q->setProperty("y", q->parentItem()->height() / 2.f);
        q->setProperty("width", 0.f);
        q->setProperty("height", 0.f);
    }
}
