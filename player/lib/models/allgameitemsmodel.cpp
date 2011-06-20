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

using namespace GluonPlayer;

class AllGameItemsModel::Private
{
public:
    Private() {
    }

    QMap<QString, GameItem*> m_gameItems;
};

AllGameItemsModel::AllGameItemsModel(QObject* parent)
    : QAbstractListModel(parent)
    , d(new Private())
{
    QDir m_dir;
    m_dir.cd(GluonCore::Global::dataDirectory() + "/gluon/games");
    QStringList gameDirNameList = m_dir.entryList(QStringList()
                                  << QString('*' + GluonEngine::projectSuffix), QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(const QString & gameDirName, gameDirNameList) {
        QDir gameDir = m_dir;
        gameDir.cd(gameDirName);
        QStringList gluonProjectFiles = gameDir.entryList(QStringList(GluonEngine::projectFilename));

        if(!gluonProjectFiles.isEmpty()) {
            QString projectFileName = gameDir.absoluteFilePath(gluonProjectFiles.at(0));
            GluonEngine::GameProject project;
            project.loadFromFile(projectFileName);
            QString id = project.property("id").toString();
            GameItem* gameItem = new GameItem(project.name(), project.description(), GameItem::Installed, id, this);
            d->m_gameItems.insert(id, gameItem);
        }
    }

    QHash<int, QByteArray> roles;
    roles[GameNameRole] = "GameName";
    roles[GameDescriptionRole] = "GameDescription";
    roles[StatusRole] = "Status";
    roles[IDRole] = "Id";
    setRoleNames(roles);

    fetchGamesList();
}

AllGameItemsModel::~AllGameItemsModel()
{
}

QVariant AllGameItemsModel::data(const QModelIndex& index, int role) const
{
    if(index.row() < 0 || index.row() > d->m_gameItems.count())
        return QVariant();

    switch(role) {
    case Qt::UserRole:
        break;
    case Qt::DisplayRole:
    case GameNameRole:
        return d->m_gameItems.values().at(index.row())->gameName();
    case GameDescriptionRole:
        return d->m_gameItems.values().at(index.row())->gameDescription();
    case StatusRole:
        return d->m_gameItems.values().at(index.row())->status();
    case IDRole:
        return d->m_gameItems.values().at(index.row())->id();
    default:
        break;
    }

    return QVariant();
}

int AllGameItemsModel::rowCount(const QModelIndex& /* parent */) const
{
    return d->m_gameItems.count();
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

void AllGameItemsModel::processFetchedGamesList(QList< OcsGameDetails* > comments)
{
    foreach(OcsGameDetails * c, comments) {
        GameItem* gameItem = new GameItem(c->gameName(), c->gameDescription(), GameItem::Downloadable,
                                          c->id(), this);
        if (!d->m_gameItems.contains(c->id())) {
            d->m_gameItems.insert(c->id(), gameItem);
        }
    }
    reset();
}

#include "allgameitemsmodel.moc"
