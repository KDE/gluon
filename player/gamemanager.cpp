/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright 2011 Shantanu Tushar <shaan7in@gmail.com>
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

#include "gamemanager.h"

#include "models/allgameitemsmodel.h"
#include "models/downloadablegamesmodel.h"
#include "models/installedgamesmodel.h"

using namespace GluonPlayer;

GLUON_DEFINE_SINGLETON(GameManager);

class GameManager::Private
{
public:
    Private()
    {
        allGameitemsModel = 0;
        downloadableGamesModel = 0;
        installedGamesModel = 0;
    }

    AllGameItemsModel *allGameitemsModel;
    DownloadableGamesModel *downloadableGamesModel;
    InstalledGamesModel *installedGamesModel;
};

GameManager::GameManager( QObject* parent )
    : Singleton< GluonPlayer::GameManager >( parent )
    , d( new Private() )
{
    d->allGameitemsModel = new AllGameItemsModel(this);
    d->downloadableGamesModel = new DownloadableGamesModel(this);
    d->installedGamesModel = new InstalledGamesModel(this);

    d->downloadableGamesModel->setSourceModel(d->allGameitemsModel);
    d->installedGamesModel->setSourceModel(d->allGameitemsModel);
}

QObject* GameManager::allGamesModel() const
{
    return qobject_cast<QObject*>(d->allGameitemsModel);
}

QObject* GameManager::downloadableGamesModel() const
{
    return qobject_cast<QObject*>(d->downloadableGamesModel);
}

QObject* GameManager::installedGamesModel() const
{
    return qobject_cast<QObject*>(d->installedGamesModel);
}

 
