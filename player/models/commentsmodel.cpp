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

#include "commentsmodel.h"
#include <core/gluonobject.h>
#include <core/gdlhandler.h>
#include <core/gluon_global.h>

#include <attica/comment.h>
#include <attica/listjob.h>

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDebug>

using namespace GluonCore;
using namespace GluonPlayer;

static const char serviceURI[] = "gamingfreedom.org";

CommentsModel::CommentsModel(QObject* parent) : QAbstractItemModel(parent)
{
    m_columnNames << "Author" << "Title" << "Body" << "DateTime" << "Rating";
    rootNode = new GluonObject("Comment");

    loadData();     //Load comments stored locally
    updateData();   //Fetch latest comments from the web service
}

void CommentsModel::updateData()
{
    connect(&m_manager, SIGNAL(defaultProvidersLoaded()), SLOT(providersUpdated()));
    m_manager.loadDefaultProviders();
}

void CommentsModel::providersUpdated()
{
    if (!m_manager.providers().isEmpty()) {
        m_provider = m_manager.providerByUrl(QUrl("https://api.opendesktop.org/v1/"));
        if (!m_provider.isValid()) {
            qDebug() << "Could not find opendesktop.org provider.";
            return;
        }

        //TODO: 128637 is the ID for Invaders, make it work for other games as well
        //      when we have more games

        Attica::ListJob<Attica::Comment>* job = m_provider.requestComments(Attica::Comment::ContentComment,
                                                "128637", "0", 0, 100);
        connect(job, SIGNAL(finished(Attica::BaseJob*)), SLOT(processFetchedComments(Attica::BaseJob*)));
        job->start();
    } else {
        qDebug() << "No providers found.";
    }
}

void CommentsModel::processFetchedComments(Attica::BaseJob* job)
{
    qDebug() << "Comments Successfully Fetched from the server";

    Attica::ListJob<Attica::Comment> *commentsJob = static_cast<Attica::ListJob<Attica::Comment>*>(job);
    if (commentsJob->metadata().error() == Attica::Metadata::NoError) {
        //No error, try to remove exising comments (if any)
        //and add new comments

        if (rootNode) {
            qDeleteAll(rootNode->children());
        }

        for (int i = 0; i < commentsJob->itemList().count(); ++i) {
            Attica::Comment p(commentsJob->itemList().at(i));
            addComment(p, rootNode);
        }

        reset();    //Reset the model to notify views to reload comments
    } else {
        qDebug() << "Could not fetch information";
    }
}

GluonObject* CommentsModel::addComment(Attica::Comment comment, GluonObject* parent)
{
    GluonObject *newComment = new GluonObject("Comment", parent);
    newComment->setProperty("Author", comment.user());
    newComment->setProperty("Title", comment.subject());
    newComment->setProperty("Body", comment.text());
    newComment->setProperty("DateTime", comment.date());
    newComment->setProperty("Rating", comment.score());

    for (int i = 0; i < comment.childCount(); i++) {
        addComment(comment.children().at(0), newComment);
    }

    return newComment;
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
    saveData();     //Save data before exiting
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
    Q_UNUSED(parent);
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

    return QAbstractItemModel::flags(index);
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
    if (count != 1) { //Don't support more than one row at a time
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
