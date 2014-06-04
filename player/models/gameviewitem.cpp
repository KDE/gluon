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

//#include <engine/projectmetadata.h>

using namespace GluonPlayer;

class GameViewItem::Private
{
    public:
    Private() //: metaData(0)    //TODO: restore after engine port
    {
    }

    //GluonEngine::ProjectMetaData* metaData;
    QStringList screenshotUrls;
    Status status;
};

GameViewItem::GameViewItem( const QString& projectFilePath, const Status& status, QObject* parent )
    : QObject( parent )
    , d( new Private )
{
    //d->metaData = new GluonEngine::ProjectMetaData(this);
    //d->metaData->setProjectFilePath(projectFilePath);
    //d->metaData->load();
    d->status = status;
}

GameViewItem::GameViewItem( const QString& projectName, const QString& projectDescription,
                            const QString& projectFilePath, const Status& status,
                            const QString& projectId, QObject* parent )
    : QObject( parent )
    , d( new Private )
{
    //d->metaData = new GluonEngine::ProjectMetaData( projectFilePath, projectName, projectDescription, projectId, this );
    d->status = status;
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
    //port
    //return d->metaData->projectName();
    return QString("GameViewItem::projectName(): port me to Qt5 after engine port");
}

QString GameViewItem::projectDescription() const
{
    //port
    //return d->metaData->projectDescription();
    return QString("GameViewItem::projectDescription(): port me to Qt5 after engine port");
}

QString GameViewItem::projectDirPath() const
{
    //port
    //return d->metaData->projectDir();
    return QString("GameViewItem::projectDirPath(): port me to Qt5 after engine port");
}

QString GameViewItem::projectFilePath() const
{
    //port
    //return d->metaData->projectFilePath();
    return QString("GameViewItem::projectFilePath(): port me to Qt5 after engine port");
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
    //port
    //return d->metaData->projectId();
    return QString("GameViewItem::projectId(): port me to Qt5 after engine port");
}

//TODO: restore after engine port
/*
GluonEngine::ProjectMetaData* GameViewItem::metaData()
{
    return d->metaData;
}
*/
