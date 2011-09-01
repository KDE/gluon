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

#include "gameitem.h"

using namespace GluonPlayer;

class GameItem::Private
{
    public:
        Private()
        {
        }

        QString gameName;
        QString gameDescription;
        int rating;
        Status status;
        QString id;
};

GameItem::GameItem( const QString& gameName, const QString& gameDescription, int rating,
                    const Status& status, const QString& id, QObject* parent )
    : QObject( parent )
    , d( new Private() )
{
    d->gameName = gameName;
    d->gameDescription = gameDescription;
    d->rating = rating;
    d->status = status;
    d->id = id;
}

GameItem::~GameItem()
{
}

QString GameItem::gameName() const
{
    return d->gameName;
}

void GameItem::setGameName( const QString& gameName )
{
    d->gameName = gameName;
}

QString GameItem::gameDescription() const
{
    return d->gameDescription;
}

void GameItem::setGameDescription( const QString& gameDescription )
{
    d->gameDescription = gameDescription;
}

GameItem::Status GameItem::status() const
{
    return d->status;
}

void GameItem::setStatus( GameItem::Status status )
{
    d->status = status;
}

int GameItem::rating() const
{
    return d->rating;
}

void GameItem::setRating( int rating )
{
    d->rating = rating;
}

QString GameItem::id() const
{
    return d->id;
}

#include "gameitem.moc"
