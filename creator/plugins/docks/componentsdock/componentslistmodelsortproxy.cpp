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
