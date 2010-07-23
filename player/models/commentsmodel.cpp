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
#include <QDebug>
#include <QFile>
#include <QDir>
#include <core/gluonobject.h>
#include <attica/person.h>
#include <attica/itemjob.h>
#include <core/gdlhandler.h>
#include <core/gluon_global.h>

using namespace GluonCore;
using namespace GluonPlayer;

static const char serviceURI[] = "gamingfreedom.org";

CommentsModel::CommentsModel(QObject* parent) : QAbstractItemModel(parent)
{
    m_columnNames << "Author" << "Title" << "Body" << "DateTime" << "Rating";
    rootNode = new GluonObject("Comment");

    loadData();
}

void CommentsModel::loadData()
{
    QDir gluonDir = QDir::home();
    gluonDir.mkdir(".gluon/" + QString(serviceURI));
    gluonDir.cd(".gluon/" + QString(serviceURI));
    QString filename = gluonDir.absoluteFilePath("comments.gdl");

    QFile dataFile(filename);
    if (!dataFile.open(QIODevice::ReadOnly))
        qDebug() << "Cannot open the comments file";

    QTextStream commentReader(&dataFile);
    QString fileContents = commentReader.readAll();
    dataFile.close();

    if (fileContents.isEmpty())
        qDebug() << "Something is wrong with the comments file";

    QList<GluonObject*> comments = GluonCore::GDLHandler::instance()->parseGDL(fileContents, 0);
    rootNode = comments.at(0);
}

void CommentsModel::saveData()
{
    qDebug() << "Saving Data";
    QDir gluonDir = QDir::home();
    gluonDir.mkpath(".gluon/" + QString(serviceURI));
    gluonDir.cd(".gluon/" + QString(serviceURI));
    QString filename = gluonDir.absoluteFilePath("comments.gdl");

    QFile dataFile(filename);
    if (!dataFile.open(QIODevice::WriteOnly))
        qDebug() << "Cannot open the comments file";

    QList<const GluonObject*> comments;
    comments.append(rootNode);
    QTextStream dataWriter(&dataFile);
    dataWriter << GluonCore::GDLHandler::instance()->serializeGDL(comments);
    dataFile.close();
    qDebug() << "Saved";
}

CommentsModel::~CommentsModel()
{
    saveData();
    delete rootNode;
}

QVariant CommentsModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        GluonObject *node;
        node = static_cast<GluonObject*>(index.internalPointer());

        return node->property(columnName(Column(index.column())).toUtf8());
    }
    return QVariant();
}

int CommentsModel::columnCount(const QModelIndex& parent) const
{
    return 5;
}

int CommentsModel::rowCount(const QModelIndex& parent) const
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

QModelIndex CommentsModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex();

    GluonObject *childItem = static_cast<GluonObject*>(child.internalPointer());
    GluonObject *parentItem = qobject_cast<GluonObject*> (childItem->parent());

    if (parentItem == rootNode)
        return QModelIndex();

    GluonObject *grandParentItem = qobject_cast<GluonObject*> (parentItem->parent());
    if (!grandParentItem)
        return QModelIndex();

    return createIndex(grandParentItem->children().indexOf(parentItem), 0, parentItem);
}

QModelIndex CommentsModel::index(int row, int column, const QModelIndex& parent) const
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

QVariant CommentsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return columnName(Column(section));

    return QVariant();
}

Qt::ItemFlags CommentsModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CommentsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        GluonObject *node;
        node = static_cast<GluonObject*>(index.internalPointer());

        node->setProperty(columnName(Column(index.column())).toUtf8(), value);
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

bool CommentsModel::insertRows(int row, int count, const QModelIndex& parent)
{
    if (count!=1) { //Don't support more than one row at a time
        qDebug() << "Can insert only one comment at a time";
        return false;
    }
    if (row != rowCount(parent)) {
        qDebug() << "Can only add a comment to the end of existing comments";
        return false;
    }

    beginInsertRows(parent, row, row);
    GluonObject *parentNode;
    parentNode = static_cast<GluonObject*>(parent.internalPointer());
        
    GluonObject *newNode = new GluonObject("Comment", parentNode);
    parentNode->addChild(newNode);
    endInsertRows();

    return true;
}

QString CommentsModel::columnName(const Column col) const
{
    return m_columnNames.at(col);
}

#include "commentsmodel.moc"
