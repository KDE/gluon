/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

    QString m_gameName;
    QString m_gameDescription;
    QString m_projectDirName;
    QString m_projectFileName;
    QStringList m_screenshotUrls;
    Status m_status;
    QString m_id;
};

GameViewItem::GameViewItem( const QString& gameName, const QString& gameDescription,
                            const QString& projectDirName, const QString& projectFileName, const Status& status,
                            const QString& id, QObject* parent )
    : QObject( parent )
    , d( new Private() )
{
    d->m_gameName = gameName;
    d->m_gameDescription = gameDescription;
    d->m_projectDirName = projectDirName;
    d->m_projectFileName = projectFileName;
    d->m_status = status;
    d->m_id = id;
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
    return d->m_gameName;
}

QString GameViewItem::gameDescription() const
{
    return d->m_gameDescription;
}

QString GameViewItem::projectDirName() const
{
    return d->m_projectDirName;
}

QString GameViewItem::projectFileName() const
{
    return d->m_projectFileName;
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
    return d->m_id;
}

#include "gameviewitem.moc"
