/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include "componentmodel.h"

#include <QtCore/QMimeData>

using namespace GluonCreator;

ComponentModel::ComponentModel(QObject* parent)
    : QStringListModel(parent)
{
}

Qt::ItemFlags
ComponentModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QStringListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | defaultFlags;
    else
        return defaultFlags;
}

QStringList
ComponentModel::mimeTypes() const
{
    QStringList types;
    types << "application/gluon.text.componentclass";
    return types;
}

QMimeData*
ComponentModel::mimeData(const QModelIndexList& indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    // There should really only be one, but let's do the loop-de-loop anyway
    foreach (QModelIndex index, indexes)
    {
        if (index.isValid())
        {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;
        }
    }

    mimeData->setData("application/gluon.text.componentclass", encodedData);
    return mimeData;
}

