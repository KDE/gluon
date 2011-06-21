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
    Private() {
    }

    QString m_gameName;
    QString m_gameDescription;
    int rating;
    Status m_status;
    QString m_id;
};

GameItem::GameItem(const QString& gameName, const QString& gameDescription, int rating,
                   const Status& status, const QString& id, QObject* parent)
    : QObject(parent)
    , d(new Private())
{
    d->m_gameName = gameName;
    d->m_gameDescription = gameDescription;
    d->rating = rating;
    d->m_status = status;
    d->m_id = id;
}

GameItem::~GameItem()
{
}

QString GameItem::gameName() const
{
    return d->m_gameName;
}

QString GameItem::gameDescription() const
{
    return d->m_gameDescription;
}

GameItem::Status GameItem::status() const
{
    return d->m_status;
}

QString GameItem::id() const
{
    return d->m_id;
}

int GameItem::rating() const
{
    return d->rating;
}

#include "gameitem.moc"
