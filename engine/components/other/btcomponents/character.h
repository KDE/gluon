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

#ifndef BRAIN_H
#define BRAIN_H

#include "engine/component.h"
#include "smarts/lib/btbrain.h"
#include "engine/gluon_engine_export.h"

#include "tree.h"

class btNode;
class btPerceptionViewcone;
class btPerceptionAtom;

namespace GluonEngine
{
    class CharacterPrivate;
    class btNodeScriptable;

    class BTCOMPONENT_EXPORT Character : public GluonEngine::Component
    {
        Q_OBJECT
        GLUON_OBJECT(GluonEngine::Character)
        Q_INTERFACES(GluonEngine::Component)
        Q_PROPERTY(bool autoThink READ autoThink WRITE setAutoThink)
        Q_PROPERTY(qreal knowledgePrecision READ knowledgePrecision WRITE setKnowledgePrecision)
        Q_PROPERTY(qreal perceptionLimit READ perceptionLimit WRITE setPerceptionLimit)
        Q_PROPERTY(GluonEngine::Tree* tree READ tree WRITE setTree)
        public:
            Q_INVOKABLE Character(QObject * parent = 0);
            Character(const Character &other, QObject * parent = 0);
            virtual ~Character();
            virtual QString category() const;
            
            virtual void initialize();
			virtual void start();
            virtual void update(int elapsedMilliseconds);
            
            bool think();
            
            void setTree(Tree* newAsset);
            Tree* tree() const;
            
            void setAutoThink(bool newAutoThink);
            bool autoThink() const;
	    
			qreal knowledgePrecision() const;
			void setKnowledgePrecision(const qreal& newKnowledgePrecision);
        
			qreal perceptionLimit() const;
			void setPerceptionLimit(const qreal& newPerceptionLimit);
			
			void addViewCone(btPerceptionViewcone * viewcone);
			void addPerceptionAtom(btPerceptionAtom * atom);
        
        private Q_SLOTS:
            void treeReplaced(Tree* newTree);
            
        private:
            void initScriptNodes(btNode * node);
            
            QSharedDataPointer<CharacterPrivate> d;
    };
}

Q_DECLARE_METATYPE(GluonEngine::Character)
Q_DECLARE_METATYPE(GluonEngine::Character*)

#endif // BRAIN_H
