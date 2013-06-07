/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
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

#include "gamedetailitem.h"

#include <QtCore/QStringList>

using namespace GluonPlayer;

class GameDetailItem::Private
{
    public:
        Private()
        {
        }

        QString gameName;
        QString gameDescription;
        QString version;
        QString category;
        QString categoryName;
        QString homePage;
        QString license;
        QString changelog;
        QString projectDirName;
        QString projectFileName;
        QStringList screenshotUrls;
        int rating;
        Status status;
        QString id;
};

GameDetailItem::GameDetailItem( const QString& gameName, const QString& gameDescription, const QString& version,
                                const QString& category, const QString& categoryName, const QString& homePage,
                                const QString& license, const QString& changelog, const QString& projectDirName,
                                const QString& projectFileName, const QStringList& screenshotUrls, int rating,
                                GluonPlayer::GameDetailItem::Status status, const QString id, QObject* parent )
    : QObject( parent )
    , d( new Private() )
{
    d->gameName = gameName;
    d->gameDescription = gameDescription;
    d->version = version;
    d->category = category;
    d->categoryName = categoryName;
    d->homePage = homePage;
    d->license = license;
    d->changelog = changelog;
    d->projectDirName = projectDirName;
    d->projectFileName = projectFileName;
    d->screenshotUrls = screenshotUrls;
    d->rating = rating;
    d->status = status;
    d->id = id;
}

GameDetailItem::~GameDetailItem()
{
    delete d;
}

QString GameDetailItem::gameDescription() const
{
    return d->gameDescription;
}

QString GameDetailItem::version() const
{
    return d->version;
}

QString GameDetailItem::category() const
{
    return d->category;
}

QString GameDetailItem::categoryName() const
{
    return d->categoryName;
}

QString GameDetailItem::homePage() const
{
    return d->homePage;
}

QString GameDetailItem::license() const
{
    return d->license;
}

QString GameDetailItem::changelog() const
{
    return d->changelog;
}

QString GameDetailItem::gameName() const
{
    return d->gameName;
}

QString GameDetailItem::id() const
{
    return d->id;
}

QString GameDetailItem::projectDirName() const
{
    return d->projectDirName;
}

QString GameDetailItem::projectFileName() const
{
    return d->projectFileName;
}

QStringList GameDetailItem::screenshotUrls() const
{
    return d->screenshotUrls;
}

GameDetailItem::Status GameDetailItem::status() const
{
    return d->status;
}

int GameDetailItem::rating() const
{
    return d->rating;
}

 
