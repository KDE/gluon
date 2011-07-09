/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef BEHAVIORTREE_TREE_H
#define BEHAVIORTREE_TREE_H

#include <engine/gluon_engine_export.h>
#include <gluon/engine/asset.h>
#include <smarts/lib/btnode.h>

namespace BehaviorTree
{
    class Asset;
    class TreePrivate;
    
    class BTCOMPONENT_EXPORT Tree : public GluonEngine::Asset
    {
        Q_OBJECT
        GLUON_OBJECT(BehaviorTree::Tree)
        Q_INTERFACES(GluonEngine::Asset)
        Q_PROPERTY(btNode* behaviorTree READ behaviorTree WRITE setBehaviorTree)
        
        public:
            friend class BehaviorTree::Asset;
            
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

Q_DECLARE_METATYPE(BehaviorTree::Tree)
Q_DECLARE_METATYPE(BehaviorTree::Tree*)

#endif // BEHAVIORTREE_TREE_H
