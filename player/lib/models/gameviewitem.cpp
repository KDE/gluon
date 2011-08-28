/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
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

#include "gameviewitem.h"

using namespace GluonPlayer;

class GameViewItem::Private
{
    public:
    Private()
    {
    }

    QString projectName;
    QString projectDescription;
    QString projectDirPath;
    QString projectFilePath;
    QStringList screenshotUrls;
    Status status;
    QString projectId;
};

GameViewItem::GameViewItem( const QString& projectName, const QString& projectDescription,
                            const QString& projectDirPath, const QString& projectFilePath, const Status& status,
                            const QString& projectId, QObject* parent )
    : QObject( parent )
    , d( new Private )
{
    d->projectName = projectName;
    d->projectDescription = projectDescription;
    d->projectDirPath = projectDirPath;
    d->projectFilePath = projectFilePath;
    d->status = status;
    d->projectId = projectId;
}

GameViewItem::GameViewItem( const GameViewItem& /* other */, QObject* parent )
    : QObject( parent )
    , d( new Private() )
{
}

GameViewItem::~GameViewItem()
{
}

QString GameViewItem::projectName() const
{
    return d->projectName;
}

QString GameViewItem::projectDescription() const
{
    return d->projectDescription;
}

QString GameViewItem::projectDirPath() const
{
    return d->projectDirPath;
}

QString GameViewItem::projectFilePath() const
{
    return d->projectFilePath;
}

QStringList GameViewItem::screenshotUrls() const
{
    return d->screenshotUrls;
}

GameViewItem::Status GameViewItem::status() const
{
    return d->status;
}

QString GameViewItem::projectId() const
{
    return d->projectId;
}

#include "gameviewitem.moc"
