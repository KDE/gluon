/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Laszlo Papp <lpapp@kde.org>
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include "allgameitemsmodel.h"

#include "gameitem.h"

#include <player/lib/ocsprovider.h>
#include <player/lib/ocsgamedetailsprovider.h>

#include <core/gluon_global.h>
#include <engine/gameproject.h>

#include <QtCore/QHash>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtGui/QFileSystemModel>

using namespace GluonPlayer;

class AllGameItemsModel::Private
{
public:
    Private() {
    }

    QMap<QString, GameItem*> gameItems;
    QFileSystemModel fsModel;
};

AllGameItemsModel::AllGameItemsModel(QObject* parent)
    : QAbstractListModel(parent)
    , d(new Private())
{
    d->fsModel.setNameFilters(QStringList('*' + GluonEngine::projectSuffix));
    connect(&d->fsModel, SIGNAL(directoryLoaded(QString)), SLOT(directoryLoaded(QString)));
    d->fsModel.setRootPath(GluonCore::Global::dataDirectory() + "/gluon/games");

    QHash<int, QByteArray> roles;
    roles[GameNameRole] = "GameName";
    roles[GameDescriptionRole] = "GameDescription";
    roles[RatingRole] = "Rating";
    roles[StatusRole] = "Status";
    roles[IDRole] = "Id";
    setRoleNames(roles);

    fetchGamesList();
}

AllGameItemsModel::~AllGameItemsModel()
{
}

void AllGameItemsModel::directoryLoaded(const QString& path)
{
    if (QDir(path) != QDir(GluonCore::Global::dataDirectory() + "/gluon/games"))
        return;

    beginResetModel();
    QModelIndex parentIndex = d->fsModel.index(path);

    //Clear GameItems
    foreach(GameItem *gameItem, d->gameItems.values()) {
        delete d->gameItems.take(gameItem->id());
    }

    //Find all .gluon dirs and add them
    for (int i=0; i<d->fsModel.rowCount(parentIndex); ++i) {
        QString gameDirName = d->fsModel.fileName(d->fsModel.index(i, 0, parentIndex));
        QDir gameDir(path);
        gameDir.cd(gameDirName);

        QStringList gluonProjectFiles = gameDir.entryList(QStringList(GluonEngine::projectFilename));

        if(!gluonProjectFiles.isEmpty()) {
            QString projectFileName = gameDir.absoluteFilePath(gluonProjectFiles.at(0));
            GluonEngine::GameProject project;
            project.loadFromFile(projectFileName);
            QString id = project.property("id").toString();

            addGameProjectToList(id, project);
        }
    }

    endResetModel();
    fetchGamesList();
}

void AllGameItemsModel::addGameProjectToList(const QString& id, const GluonEngine::GameProject& project)
{
    //FIXME: Rating = 0 might not be good
    GameItem* gameItem = new GameItem(project.name(), project.description(), 0, GameItem::Installed, id, this);
    addGameItemToList(id, gameItem);
}

void AllGameItemsModel::addGameItemToList(const QString& id, GluonPlayer::GameItem* gameItem)
{
    d->gameItems.insert(id, gameItem);
}

QVariant AllGameItemsModel::data(const QModelIndex& index, int role) const
{
    if(index.row() < 0 || index.row() > d->gameItems.count())
        return QVariant();

    switch(role) {
    case Qt::UserRole:
        break;
    case Qt::DisplayRole:
    case GameNameRole:
        return d->gameItems.values().at(index.row())->gameName();
    case GameDescriptionRole:
        return d->gameItems.values().at(index.row())->gameDescription();
    case RatingRole:
        return d->gameItems.values().at(index.row())->rating();
    case StatusRole:
        return d->gameItems.values().at(index.row())->status();
    case IDRole:
        return d->gameItems.values().at(index.row())->id();
    default:
        break;
    }

    return QVariant();
}

int AllGameItemsModel::rowCount(const QModelIndex& /* parent */) const
{
    return d->gameItems.count();
}

int AllGameItemsModel::columnCount(const QModelIndex& /* parent */) const
{
    return 1;
}

QVariant AllGameItemsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(section == 0) {
        return QString("Game");
    }

    return QAbstractItemModel::headerData(section, orientation, role);
}

void AllGameItemsModel::fetchGamesList()
{
    OcsGameDetailsProvider* gameDetailsProvider = OcsProvider::instance()->fetchGames();
    connect(gameDetailsProvider, SIGNAL(gameDetailsFetched(QList<OcsGameDetails*>)),
            SLOT(processFetchedGamesList(QList<OcsGameDetails*>)));
}

void AllGameItemsModel::processFetchedGamesList(QList< OcsGameDetails* > gamesList)
{
    beginResetModel();
    foreach(OcsGameDetails * c, gamesList) {
        GameItem* gameItem = new GameItem(c->gameName(), c->gameDescription(), c->rating(), GameItem::Downloadable,
                                          c->id(), this);
        if (!d->gameItems.contains(c->id())) {
            addGameItemToList(c->id(), gameItem);
        }
    }
    endResetModel();
}

#include "allgameitemsmodel.moc"
