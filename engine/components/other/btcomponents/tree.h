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

#ifndef BEHAVIORTREE_TREE_H
#define BEHAVIORTREE_TREE_H

#include "engine/gluon_engine_export.h"
#include "engine/asset.h"
#include "smarts/lib/btnode.h"

namespace GluonEngine
{
    class btAsset;
    class TreePrivate;
    
    class BTCOMPONENT_EXPORT Tree : public GluonEngine::Asset
    {
        Q_OBJECT
        GLUON_OBJECT(GluonEngine::Tree)
        Q_INTERFACES(GluonEngine::Asset)
        Q_PROPERTY(btNode* behaviorTree READ behaviorTree WRITE setBehaviorTree)
        
        public:
            friend class GluonEngine::btAsset;
            
            Tree(QObject * parent = 0);
            Tree(const Tree& other, QObject* parent = 0);
            ~Tree();
            
            void setBehaviorTree(btNode* newBehaviorTree);
            btNode* behaviorTree() const;
		
			void setFile(QString file);
			QString getFile();
        Q_SIGNALS:
            void treeChanged(Tree* newTree);
            
        private:
            TreePrivate* d;
    };
}

Q_DECLARE_METATYPE(GluonEngine::Tree)
Q_DECLARE_METATYPE(GluonEngine::Tree*)

#endif // BEHAVIORTREE_TREE_H
