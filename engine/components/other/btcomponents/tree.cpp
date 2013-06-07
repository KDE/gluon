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

#include "tree.h"

#include "core/debughelper.h"

#include "treeprivate.h"

REGISTER_OBJECTTYPE(GluonEngine,Tree)

using namespace GluonEngine;

Tree::Tree(QObject * parent)
    : GluonEngine::Asset(parent)
{
    d = new TreePrivate(this);
}

Tree::Tree(const Tree& other, QObject* parent)
        : GluonEngine::Asset(parent)
        , d(other.d)
{

}


Tree::~Tree()
{
}

void
Tree::setBehaviorTree(GluonSmarts::btNode* newBehaviorTree)
{
    d->behaviorTree = newBehaviorTree;
}

GluonSmarts::btNode*
Tree::behaviorTree() const
{
    return d->behaviorTree;
}

void
Tree::setFile(QString file)
{
	d->file = file;
}

QString
Tree::getFile()
{
	return d->file;
}

 
