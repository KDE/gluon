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

#include <engine/projectmetadata.h>

using namespace GluonPlayer;

class GameViewItem::Private
{
    public:
    Private() : m_metaData(0)
    {
    }

    GluonEngine::ProjectMetaData* m_metaData;
    QStringList m_screenshotUrls;
    Status m_status;
};

GameViewItem::GameViewItem( const QString& projectFileName, const Status& status, QObject* parent )
    : QObject( parent )
    , d( new Private() )
{
    d->m_metaData = new GluonEngine::ProjectMetaData(this);
    d->m_metaData->setProjectPath(projectFileName);
    d->m_metaData->load();
    d->m_status = status;
}

GameViewItem::GameViewItem( const QString& gameName, const QString& gameDescription,
                            const QString& projectFileName, const Status& status,
                            const QString& id, QObject* parent )
    : QObject( parent )
    , d( new Private() )
{
    d->m_metaData = new GluonEngine::ProjectMetaData( projectFileName, gameName, gameDescription, id, this );
    d->m_status = status;
}


GameViewItem::GameViewItem( const GameViewItem& /* other */, QObject* parent )
    : QObject( parent )
    , d( new Private() )
{
}

GameViewItem::~GameViewItem()
{
}

QString GameViewItem::gameName() const
{
    return d->m_metaData->projectName();
}

QString GameViewItem::gameDescription() const
{
    return d->m_metaData->description();
}

QString GameViewItem::projectDirName() const
{
    return d->m_metaData->projectDir();
}

QString GameViewItem::projectFileName() const
{
    return d->m_metaData->projectPath();
}

QStringList GameViewItem::screenshotUrls() const
{
    return d->m_screenshotUrls;
}

GameViewItem::Status GameViewItem::status() const
{
    return d->m_status;
}

QString GameViewItem::id() const
{
    return d->m_metaData->id();
}

GluonEngine::ProjectMetaData* GameViewItem::metaData()
{
    return d->m_metaData;
}

#include "gameviewitem.moc"
