/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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


#ifndef QOBJECTTREEMODEL_H
#define QOBJECTTREEMODEL_H

#include <QtCore/QAbstractItemModel>

namespace Gluon
{

    namespace Creator
    {

        class QObjectTreeModel : public QAbstractItemModel
        {
            public:
                explicit QObjectTreeModel(QObject* root, QObject* parent = 0);
                virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
                virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
                virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
                virtual QModelIndex parent(const QModelIndex& child) const;
                virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
                virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

            protected:
                QObject *m_root;
                int rowIndex(QObject* object) const;
        };
    }
}

#endif // QOBJECTTREEMODEL_H
