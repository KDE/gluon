/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "componentslistmodelsortproxy.h"
#include "models/componentmodel.h"
#include "core/debughelper.h"

#include <QtCore/QMimeData>

using namespace GluonCreator;

ComponentsListModelSortProxy::ComponentsListModelSortProxy(QObject* parent)
    : KCategorizedSortFilterProxyModel(parent)
{
}

ComponentsListModelSortProxy::~ComponentsListModelSortProxy()
{
}
/*
QVariant
ComponentsListModelSortProxy::data(const QModelIndex& index, int role) const
{
    DEBUG_BLOCK
    if(!index.isValid())
        return QVariant();
    
    if(role == KCategorizedSortFilterProxyModel::CategoryDisplayRole || role == KCategorizedSortFilterProxyModel::CategorySortRole)
    {
        DEBUG_TEXT(QString("Fetching category data"));
        return sourceModel()->data(createIndex(index.row(), 1, 0), Qt::DisplayRole);
    }
    return sourceModel()->data(index, role);
}

QVariant
ComponentsListModelSortProxy::headerData(int section, Qt::Orientation orientation, int role) const
{
    return sourceModel()->headerData(section, orientation, role);
}

QModelIndex
ComponentsListModelSortProxy::index(int row, int column, const QModelIndex& parent) const
{
    if(parent.isValid())
        return QModelIndex();
    if(row < 0 || column < 0)
        return QModelIndex();
    if(row >= sourceModel()->rowCount() ||column >= sourceModel()->columnCount())
        return QModelIndex();
    
//    QModelIndex idx = sourceModel()->index(row, column, parent);
//    return createIndex(idx.row(), idx.column(), (quint32)idx.internalId());
    return createIndex(row, column, 0);
}

QModelIndex
ComponentsListModelSortProxy::parent(const QModelIndex& index) const
{
    QModelIndex idx = sourceModel()->parent(index);
    if(idx.isValid())
        return createIndex(idx.row(), idx.column(), 0);
    return QModelIndex();
}

Qt::ItemFlags
ComponentsListModelSortProxy::flags(const QModelIndex& index) const
{
    return sourceModel()->flags(index);
}

QMimeData*
ComponentsListModelSortProxy::mimeData(const QModelIndexList& indexes) const
{
    return sourceModel()->mimeData(indexes);
}

QStringList
ComponentsListModelSortProxy::mimeTypes() const
{
    return sourceModel()->mimeTypes();
}

int ComponentsListModelSortProxy::columnCount(const QModelIndex& parent) const
{
    return sourceModel()->columnCount(parent);
}

int ComponentsListModelSortProxy::rowCount(const QModelIndex& parent) const
{
    return sourceModel()->rowCount(parent);
}

bool
ComponentsListModelSortProxy::hasChildren(const QModelIndex& index) const
{
    return sourceModel()->rowCount(index);
}*/

bool
ComponentsListModelSortProxy::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    QVariant lData = sourceModel()->data(left);
    QVariant rData = sourceModel()->data(right);
    return lData.toString() < rData.toString();
}

bool
ComponentsListModelSortProxy::subSortLessThan(const QModelIndex& left, const QModelIndex& right) const
{
    QVariant lData = sourceModel()->data(left);
    QVariant rData = sourceModel()->data(right);
    return lData.toString() < rData.toString();
}

int
ComponentsListModelSortProxy::compareCategories(const QModelIndex& left, const QModelIndex& right) const
{
    if(left.isValid() && right.isValid() && isCategorizedModel())
    {
        return
            sourceModel()->data(sourceModel()->index(left.row(), 1, left.parent()), Qt::DisplayRole).toString() <
            sourceModel()->data(sourceModel()->index(right.row(), 1, right.parent()), Qt::DisplayRole).toString();
    }
    return KCategorizedSortFilterProxyModel::lessThan( left, right );
}

#include "componentslistmodelsortproxy.moc"
