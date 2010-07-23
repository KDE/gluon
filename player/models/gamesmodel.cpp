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
#include <core/gluon_global.h>
#include <engine/gameproject.h>

#include <QDir>
#include <QCoreApplication>
#include <QDebug>

using namespace GluonPlayer;

GamesModel::GamesModel(QObject* parent) : QAbstractTableModel(parent)
{
#ifdef Q_WS_X11
        m_dir.cd(GluonCore::Global::dataDirectory() + "/gluon/games");
#endif
	
#ifdef Q_WS_MAC
	m_dir.cd(QCoreApplication::applicationDirPath() + "/../games");
#endif

}

QVariant GamesModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        QString gameDirName = m_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).at(index.row());
        QDir gameDir = m_dir;
        gameDir.cd(gameDirName);
        QStringList gluonProjectFiles = gameDir.entryList(QStringList("*.gluon"));
        QString projectFileName = gameDir.absoluteFilePath(gluonProjectFiles.at(0));

        if (!gluonProjectFiles.isEmpty()) {
            if (index.column() == PathColumn) {
                return projectFileName;
            } else {
                GluonEngine::GameProject project;
                project.loadFromFile(projectFileName);
                switch (index.column()) {
                case NameColumn:
                    return project.name();
                    break;
                case DescriptionColumn:
                    return project.description();
                    break;
                }
            }
        } else {
            return QVariant();
        }
    }

    return QVariant();
}

int GamesModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 3;
}

int GamesModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).count();
}

QVariant GamesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section == 0) {
        return QString("Game");
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}
