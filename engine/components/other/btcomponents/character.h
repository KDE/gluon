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

#ifndef BRAIN_H
#define BRAIN_H

#include <engine/component.h>
#include <smarts/lib/btbrain.h>
#include <engine/gluon_engine_export.h>
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
        Q_CLASSINFO( "org.gluon.category", "Behavior Tree" )
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
