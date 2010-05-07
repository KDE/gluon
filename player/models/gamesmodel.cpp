/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar Jha <jhahoneyk@gmail.com>
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

#include "gamesmodel.h"

#include <QDir>
#include <QCoreApplication>

using namespace GluonPlayer;

GamesModel::GamesModel(QObject* parent): QAbstractTableModel(parent)
{
    m_dir.cd(QCoreApplication::applicationDirPath() + "/../share/gluon/games");
}

QVariant GamesModel::data(const QModelIndex& index, int role) const
{
    QString gameDirName = m_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).at(index.row());
    QDir gameDir = m_dir;
    gameDir.cd(gameDirName);
    QStringList gluonProjectFiles = gameDir.entryList(QStringList("*.gluon"));

    if (!gluonProjectFiles.isEmpty()) {
        return gameDir.absoluteFilePath(gluonProjectFiles.at(0));
    } else {
        return QVariant();
    }
}

int GamesModel::columnCount(const QModelIndex& parent) const
{
    return 1;   //Later we will add more columns for more details about each game
}

int GamesModel::rowCount(const QModelIndex& parent) const
{
    return m_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).count();
}

QVariant GamesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section == 0) {
        return QString("Game");
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

