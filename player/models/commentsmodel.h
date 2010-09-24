/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
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

#ifndef GLUONPLAYER_COMMENTSMODEL_H
#define GLUONPLAYER_COMMENTSMODEL_H

#include <attica/providermanager.h>
#include <attica/provider.h>
#include "gluon_player_export.h"

#include <QAbstractItemModel>
#include <QStringList>


namespace Attica
{
    class BaseJob;
}

namespace GluonCore
{
    class GluonObject;
};

namespace GluonPlayer
{

    class GLUON_PLAYER_EXPORT CommentsModel : public QAbstractItemModel
    {
            Q_OBJECT

        public:
            enum Column { AuthorColumn, TitleColumn, BodyColumn, DateTimeColumn, RatingColumn };

            CommentsModel(QObject* parent = 0);
            virtual ~CommentsModel();
            virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
            virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
            virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
            virtual QModelIndex parent(const QModelIndex& child) const;
            virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
            virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
            virtual Qt::ItemFlags flags(const QModelIndex &index) const;
            virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
            virtual bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());

            QString columnName(const Column col) const;
            bool isOnline();
            void addComment(const QModelIndex& parentIndex, const QString& subject, const QString& message);

        private:
            GluonCore::GluonObject *rootNode;
            QStringList m_columnNames;
            bool m_isOnline;

            void updateData();
            void loadData();
            void saveData();

            GluonCore::GluonObject *addComment(Attica::Comment comment, GluonCore::GluonObject *parent);

        private slots:
            void providersUpdated();
            void processFetchedComments(Attica::BaseJob*);
            void addCommentFinished(Attica::BaseJob* job);

        signals:
            void addCommentFailed();
    };

}

#endif // GLUONPLAYER_COMMENTSMODEL_H
