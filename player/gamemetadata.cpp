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


#include "gamemetadata.h"

#include "gamemanager.h"
#include "models/allgameitemsmodel.h"

#include <engine/projectmetadata.h>

#include <QDebug>

using namespace GluonPlayer;

class GameMetadata::Private
{
    public:
        Private()
        {
            projectMetadata = 0;
        }

        GluonEngine::ProjectMetaData* projectMetadata;
        QString gameId;
        QString gameName;
        QString gameDescription;
};

GameMetadata::GameMetadata( QObject* parent )
    : QObject( parent )
    , d(new Private())
{
    d->projectMetadata = new GluonEngine::ProjectMetaData(this);
}

GameMetadata::~GameMetadata()
{
    delete d;
}

QString GameMetadata::gameId() const
{
    return d->gameId;
}

void GameMetadata::setGameId( const QString& gameId )
{
    AllGameItemsModel *model = qobject_cast<AllGameItemsModel*>(GameManager::instance()->allGamesModel());
    QString gamePath = model->data(gameId, AllGameItemsModel::UriRole).toString();

    if (!gamePath.isEmpty() && QFileInfo(gamePath).exists())
    {
        d->gameId = gameId;

        d->projectMetadata->setProjectFilePath(gamePath);
        d->projectMetadata->load();

        d->gameName = d->projectMetadata->projectName();
        d->gameDescription = d->projectMetadata->projectDescription();
    } else {
        d->gameId = model->data(gameId, AllGameItemsModel::IdRole).toString();
        d->gameName = model->data(gameId, AllGameItemsModel::GameNameRole).toString();
        d->gameDescription = model->data(gameId, AllGameItemsModel::GameDescriptionRole).toString();
    }

    emit gameIdChanged();
    emit gameNameChanged();
    emit gameDescriptionChanged();
}

QString GameMetadata::gameName() const
{
    return d->gameName;
}

QString GameMetadata::gameDescription() const
{
    return d->gameDescription;
}

 
