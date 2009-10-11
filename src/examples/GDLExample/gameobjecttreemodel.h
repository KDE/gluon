/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef GAMEOBJECTTREEMODEL_H
#define GAMEOBJECTTREEMODEL_H

#include <qt4/QtCore/QAbstractItemModel>

namespace Gluon
{
    class GameObject;
}

class GameObjectTreeModel : public QAbstractItemModel
{
    public:
        GameObjectTreeModel(Gluon::GameObject* root, QObject* parent = 0);
        virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
        virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
        virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
        virtual QModelIndex parent(const QModelIndex& child) const;
        virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
        virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
        
    protected:
        Gluon::GameObject *m_root;
        int rowIndex(Gluon::GameObject* object) const;
};

#endif // GAMEOBJECTTREEMODEL_H
