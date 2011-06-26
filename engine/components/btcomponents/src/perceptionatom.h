#ifndef PERCEPTIONATOM_H
#define PERCEPTIONATOM_H

#include "bt_export.h"

#include <engine/component.h>
#include <QtCore/QObject>
#include <QtCore/QSharedData>
#include "perceptioninfo.h"

namespace BehaviorTree
{
	class PerceptionAtomPrivate;
	class PerceptionInfo;
	
	class BTCOMPONENT_EXPORT PerceptionAtom : public GluonEngine::Component
	{
		Q_OBJECT
                GLUON_OBJECT(BehaviorTree::PerceptionAtom)
		Q_INTERFACES(GluonEngine::Component)
		
		Q_PROPERTY(BehaviorTree::PerceptionInfo* perceptionInfo READ perceptionInfo WRITE setPerceptionInfo)
		Q_PROPERTY(QVariant knowledge READ knowledge)
		Q_PROPERTY(qreal precision READ precision WRITE setPrecision)
		Q_PROPERTY(bool shouldUpdate READ shouldUpdate WRITE setShouldUpdate)
		
		public:
			PerceptionAtom(QObject* parent = 0);
			PerceptionAtom(const PerceptionAtom& other, QObject* parent = 0);
			~PerceptionAtom();
			
			virtual void initialize();
			
			void setPerceptionInfo(BehaviorTree::PerceptionInfo* info);
            BehaviorTree::PerceptionInfo* perceptionInfo() const;
			
			QVariant knowledge() const;
			
			qreal precision() const;
			void setPrecision(qreal precision);
			
			bool shouldUpdate() const;
			void setShouldUpdate(bool update);
			
		private:
			QSharedDataPointer<PerceptionAtomPrivate> d;
	};
}

Q_DECLARE_METATYPE(BehaviorTree::PerceptionAtom)
Q_DECLARE_METATYPE(BehaviorTree::PerceptionAtom*)

#endif
