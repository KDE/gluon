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

#include "character.h"

#include <QtCore/QVariant>
#include <QtCore/QMetaProperty>

#include "core/gluonobjectfactory.h"
#include "core/debughelper.h"

#include "engine/gameobject.h"
#include "engine/game.h"
#include "engine/gameproject.h"
#include "engine/asset.h"

#include "smarts/lib/btperceptionatom.h"
#include "smarts/lib/btperceptionviewcone.h"

#include "btcharacterscriptable.h"
#include "characterprivate.h"
#include "tree.h"
#include "btnodescriptable.h"

#include <QDebug>

REGISTER_OBJECTTYPE(GluonEngine,Character)

using namespace GluonEngine;

Character::Character(QObject* parent)
        : GluonEngine::Component(parent)
{
    d = new CharacterPrivate;

// #warning Q_PROPERTY does not currently handle namespaced types - see bugreports.qt.nokia.com/browse/QTBUG-2151
//     setTree(NULL);
    d->self = new btCharacterScriptable();
    d->perception = d->self->perception();
};

Character::Character(const Character &other, QObject * parent)
        : Component(parent)
        , d(other.d)
{
}

Character::~Character()
{
}

QString Character::category() const
{
    return QString(tr("Behavior Tree"));
}

void Character::initialize()
{
}

void Character::start()
{
//     DEBUG_BLOCK
    if (tree())
    {
        initScriptNodes(tree()->behaviorTree());
    }
    else
    {
        debug("Can not init behavior tree. Behavior tree is not set");
    }
}

void
Character::update(int elapsedMilliseconds)
{
    //debug(QString("Updating Character"));
    this->setProperty("time", elapsedMilliseconds);
    this->setProperty("elapsedTime", QVariant(this->property("elapsedTime").toInt() + elapsedMilliseconds));
    if (autoThink())
        think();
    Component::update(elapsedMilliseconds);
}

bool
Character::think()
{
    bool thoughtSuccessful = false;
    //debug(QString("Thinking..."));
    QString debugText;
    if (tree())
    {
        if (tree()->behaviorTree())
        {
            d->self->think();
            debugText += "Thinking!";
            thoughtSuccessful = true;
        }
        else
            debugText += "Thinking not possible - behavoirTree not set!";
    }
    else
        debugText += "Thinking not possible - no tree!";
    //debug(debugText);
    return thoughtSuccessful;
}

void
Character::treeReplaced(Tree* newTree)
{
    setTree(newTree);
}

void
Character::setTree(Tree* newAsset)
{
    DEBUG_BLOCK
    if (newAsset) {
        DEBUG_TEXT(QString("Setting tree to %1").arg(newAsset->name()))
    }

    if (d->tree)
        disconnect(d->tree, SIGNAL(treeChanged(Tree*)), this, SLOT(treeReplaced(Tree*)));
    d->tree = newAsset;

    if (d->tree)
	{
        d->self->setBehaviorTree(d->tree->behaviorTree());
	}

//     QVariant theNewValue;
//     theNewValue.setValue<Tree*>(newAsset);
//     setProperty("tree", theNewValue);

    if (d->tree)
        connect(d->tree, SIGNAL(treeChanged(Tree*)), this, SLOT(treeReplaced(Tree*)));
}

Tree*
Character::tree() const
{
    return d->tree;
//     Tree* returnTree = NULL;
//     GluonObject* theTree = this->property("tree").value<GluonObject*>();
//     if (qobject_cast<Tree*>(theTree))
//         returnTree = qobject_cast<Tree*>(theTree);
//     return returnTree;
}

void
Character::setAutoThink(bool newAutoThink)
{
    d->autoThink = newAutoThink;
}

bool
Character::autoThink() const
{
    return d->autoThink;
}

qreal Character::knowledgePrecision() const
{
    return d->perception->knowledgePrecision();
}

void Character::setKnowledgePrecision(const qreal& newKnowledgePrecision)
{
    d->perception->setKnowledgePrecision(newKnowledgePrecision);
}

qreal Character::perceptionLimit() const
{
    return d->perception->perceptionLimit();
}

void Character::setPerceptionLimit(const qreal& newPerceptionLimit)
{
    d->perception->setPerceptionLimit(newPerceptionLimit);
}

void Character::addViewCone(GluonSmarts::btPerceptionViewcone * viewcone)
{
    d->perception->addViewCone(viewcone);
}

void Character::addPerceptionAtom(GluonSmarts::btPerceptionAtom * atom)
{
    d->perception->addPerceptionAtom(atom);
}

void Character::initScriptNodes(GluonSmarts::btNode* node)
{
    if (node->type() == GluonSmarts::btNode::UnusableNodeType)
    {
        QList<GluonEngine::Asset*> assets = GluonEngine::Game::instance()->gameProject()->findChildren<GluonEngine::Asset*>();
        foreach(GluonEngine::Asset* asset, assets)
        {
            if (QString(asset->metaObject()->className()) == QString("GluonEngine::ScriptAsset") 
                && node->className() == asset->name().left(asset->name().lastIndexOf("."))
                && QString(node->metaObject()->className()) != QString("GluonEngine::btNodeScriptable"))
            {
                btNodeScriptable * newNode = new btNodeScriptable(this);
                
                for(int i = 0; i < node->metaObject()->propertyCount(); i++)
                {
                    QString propertyName = node->metaObject()->property(i).name();
                    if(propertyName == "objectName")  
                    {
                        continue;
                    }
        
                    newNode->setProperty(propertyName.toUtf8(), node->property(propertyName.toUtf8()));
                }
                
                for(int i = 0; i < node->dynamicPropertyNames().count(); i++)
                {
                    QString propertyName(node->dynamicPropertyNames().at(i));
                    
                    newNode->setProperty(propertyName.toUtf8(), node->property(propertyName.toUtf8()));
                }
                
                for(int i = 0; i < node->childCount(); i++)
                {
                    newNode->appendChild(node->child(i));
                    node->child(i)->setParentNode(newNode);
                }               
                
                for(int i = 0; i < newNode->childCount(); i++)
                {
                    node->removeChild(i);
                }
                
                GluonSmarts::btNode* parent = node->parentNode();
                int childIndex = parent->childIndex(node);
                parent->removeChild(node);
                parent->insertChild(childIndex,newNode);
                newNode->setParentNode(parent);
                newNode->setScriptAsset(asset);

                delete node;
                node = newNode;
                break;
            }
        }
    }
    
    for (int i = 0; i < node->childCount(); i++)
        initScriptNodes(node->child(i));
}



 
