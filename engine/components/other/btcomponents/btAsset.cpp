/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "btAsset.h"

#include "smarts/lib/btbrain.h"

#include "btAssetprivate.h"
#include "tree.h"

#include <QtCore/QVariant>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QMap>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <game.h>

Q_DECLARE_METATYPE(GluonSmarts::btNode*)

REGISTER_OBJECTTYPE(GluonEngine, btAsset)

using namespace GluonEngine;

btAsset::btAsset(QObject * parent)
    : GluonEngine::Asset(parent)
{
    d = new btAssetPrivate;
    qRegisterMetaType<GluonSmarts::btNode*>("btNode*");
}

btAsset::btAsset(const btAsset& other, QObject* parent)
        : GluonEngine::Asset(parent)
        , d(other.d)
{

}

btAsset::~btAsset()
{
    delete d;
}

void
btAsset::setFile(const QString& newFile)
{
    debug(QString("Attempting to load %1").arg(newFile));
    QString newPath = Game::instance()->gameProject()->dirname().toLocalFile() + '/' + newFile;
    QFile *brainFile = new QFile( newPath );
    if(!brainFile->open(QIODevice::ReadOnly))
        return;

    debug(QString("File opened, attempting to create brain"));
    QTextStream brainReader(brainFile);
    GluonSmarts::btBrain* newBrain = new GluonSmarts::btBrain(brainReader.readAll(), newPath );
    brainFile->close();
    delete brainFile;

    if(!newBrain)
        return;

    debug(QString("Brain loaded, replacing old brain and creating %1 sub-btAssets").arg(newBrain->behaviorTreesCount()));
    //delete d->brain;
    d->brain = newBrain;

    const QObjectList& oldChildren = children();
    QList<Tree*> newChildren;
    for(int i = 0; i < newBrain->behaviorTreesCount(); ++i)
    {
        Tree* newTree = new Tree(this);
        this->addChild(newTree);
        newTree->setBehaviorTree(newBrain->getBehaviorTree(i));
        newTree->setName(newTree->behaviorTree()->name());
        newChildren.append(newTree);
    }

    // Run through all old children
    foreach(QObject* oldChild, oldChildren)
    {
        Tree* theNewChild = NULL;
        Tree* theOldChild = qobject_cast<Tree*>(oldChild);
        // Find a tree with the same name in the new children
        foreach(Tree* newChild, newChildren)
        {
            if(newChild->name() == theOldChild->name())
                theNewChild = newChild;
        }
        // Tell old child that new child is the tree that should be used
        // If no new child could be found, inform the oldChild that it should be removed
        emit theOldChild->treeChanged(theNewChild);
    }

    debug(QString("Brain successfully loaded! Number of sub-btAssets created: %1").arg(this->children().count()));

//    qDeleteAll(oldChildren);

    GluonEngine::Asset::setFile(newFile);
}

const QStringList
btAsset::supportedMimeTypes() const
{
	QStringList list;
	list.append("application/xml");
	return list;
}

//we only need to use this macro here, because we are registering and handling the other components and btAssets through the GLUON_OBJECT
Q_EXPORT_PLUGIN2(gluon_plugin_Asset_behaviortree, GluonEngine::btAsset)

#include "btAsset.moc"
