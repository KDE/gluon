/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) <year> <author> <email@example.com>
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

#ifndef GAMESMODEL_H
#define GAMESMODEL_H

#include <QAbstractListModel>
#include <QDir>

#include "gluon_player_export.h"

namespace GluonPlayer
{
    class GLUON_PLAYER_EXPORT GamesModel : public QAbstractListModel
    {
        Q_OBJECT

    public:
        GamesModel(QObject* parent = 0);
        virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
        virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;

    private:
        QDir m_dir;
    };
}

#endif // GAMESMODEL_H
