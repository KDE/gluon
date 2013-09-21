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

#include "dockeroverlay.h"

#include <QRect>
#include <KDE/KApplication>
#include <QTimer>

class QTimer;
class QRect;
class KApplication;

class DockerOverlay::Private
{
    public:
        Private( DockerOverlay* qq ) : q( qq ) { }
        void updateDocker();

        DockerOverlay* q;
        QString dockerName;
};

DockerOverlay::DockerOverlay( QDeclarativeItem* parent )
    : QDeclarativeItem( parent ), d( new Private( this ) )
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
    QWidget* docker = kapp->activeWindow()->findChild<QWidget*>(dockerName);

    if( docker )
    {
        QRect dockerGeometry = docker->frameGeometry();

        q->setX(dockerGeometry.x());
        q->setY(dockerGeometry.y());
        q->setWidth(dockerGeometry.width());
        q->setHeight(dockerGeometry.height());
    }
    else
    {
        q->setX(q->parentItem()->width() / 2.f);
        q->setY(q->parentItem()->height() / 2.f);
        q->setWidth(0.f);
        q->setHeight(0.f);
    }
}
