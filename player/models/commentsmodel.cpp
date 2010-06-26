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

#include "commentsmodel.h"
#include <core/gluonobject.h>

using namespace GluonCore;
using namespace GluonPlayer;

CommentsModel::CommentsModel (QObject* parent) : QAbstractItemModel (parent)
{
    m_columnNames << "Author" << "Title" << "Body" << "DateTime" << "Rating";
    rootNode = new GluonObject("Comment");

    //Some dummy comments, we gotta check it, right? ;)
    GluonObject *comment = new GluonObject("This is a comment");
    comment->setPropertyFromString(columnName(AuthorColumn), "string(Shantanu)");
    comment->setPropertyFromString(columnName(TitleColumn), "string(Nice comment!)");
    comment->setPropertyFromString(columnName(BodyColumn), "string(This is the body of the comment)");
    comment->setPropertyFromString(columnName(DateTimeColumn), "string(Date Time)");
    comment->setPropertyFromString(columnName(RatingColumn), "int(5)");
    rootNode->addChild(comment);
    
    GluonObject *comment2 = new GluonObject("This comment2");
    comment2->setPropertyFromString(columnName(AuthorColumn), "string(Leinir)");
    comment2->setPropertyFromString(columnName(TitleColumn), "string(Bad comment!)");
    comment2->setPropertyFromString(columnName(BodyColumn), "string(I'm happy)");
    comment2->setPropertyFromString(columnName(DateTimeColumn), "string(Bate gime)");
    comment2->setPropertyFromString(columnName(RatingColumn), "int(10)");
    comment->addChild(comment2);
}

CommentsModel::~CommentsModel()
{
    delete rootNode;
}

QVariant CommentsModel::data (const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        GluonObject *node;
        node = static_cast<GluonObject*>(index.internalPointer());
        
        //TODO: The format is not proper -Shaan7
        return node->getStringFromProperty(columnName(Column(index.column())), "$").remove(0, 1);
    }
    return QVariant();
}

int CommentsModel::columnCount (const QModelIndex& parent) const
{
    return 5;
}

int CommentsModel::rowCount (const QModelIndex& parent) const
{
    GluonObject *parentItem;
     if (parent.column() > 0)
         return 0;

     if (!parent.isValid())
         parentItem = rootNode;
     else
         parentItem = static_cast<GluonObject*>(parent.internalPointer());

     return parentItem->children().count();
}

QModelIndex CommentsModel::parent (const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex();

    GluonObject *childItem = static_cast<GluonObject*>(child.internalPointer());
    GluonObject *parentItem = qobject_cast<GluonObject*>(childItem->parent());

    if (parentItem == rootNode)
        return QModelIndex();

    GluonObject *grandParentItem = qobject_cast<GluonObject*>(parentItem->parent());
    if (!grandParentItem)
        return QModelIndex();
    
     return createIndex(grandParentItem->children().indexOf(parentItem), 0, parentItem);
}

QModelIndex CommentsModel::index (int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
         return QModelIndex();

     GluonObject *parentItem;

     if (!parent.isValid())
         parentItem = rootNode;
     else
         parentItem = static_cast<GluonObject*>(parent.internalPointer());

     GluonObject *childItem = parentItem->child(row);
     if (childItem)
         return createIndex(row, column, childItem);
     else
         return QModelIndex();
}

QVariant CommentsModel::headerData (int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
         return columnName(Column(section));

     return QVariant();
}

QString CommentsModel::columnName (const Column col) const
{
    return m_columnNames.at(col);
}

