#ifndef PERCEPTIONATOM_H
#define PERCEPTIONATOM_H

#include <engine/gluon_engine_export.h>
#include <engine/component.h>
#include <QtCore/QObject>
#include <QtCore/QSharedData>
#include "perceptioninfo.h"

namespace GluonEngine
{
	class PerceptionAtomPrivate;
	class PerceptionInfo;
	
        class BTCOMPONENT_EXPORT PerceptionAtom : public GluonEngine::Component
	{
		Q_OBJECT
                GLUON_OBJECT(GluonEngine::PerceptionAtom)
		Q_INTERFACES(GluonEngine::Component)
		
                Q_PROPERTY(GluonEngine::PerceptionInfo* perceptionInfo READ perceptionInfo WRITE setPerceptionInfo)
		Q_PROPERTY(QVariant knowledge READ knowledge)
		Q_PROPERTY(qreal precision READ precision WRITE setPrecision)
		Q_PROPERTY(bool shouldUpdate READ shouldUpdate WRITE setShouldUpdate)
                Q_CLASSINFO( "org.gluon.category", "Behavior Tree" );
		public:
                        Q_INVOKABLE PerceptionAtom(QObject* parent = 0);
			PerceptionAtom(const PerceptionAtom& other, QObject* parent = 0);
			~PerceptionAtom();
                        virtual QString category() const;
			
			virtual void initialize();
			
                        void setPerceptionInfo(GluonEngine::PerceptionInfo* info);
            GluonEngine::PerceptionInfo* perceptionInfo() const;
			
			QVariant knowledge() const;
			
			qreal precision() const;
			void setPrecision(qreal precision);
			
			bool shouldUpdate() const;
			void setShouldUpdate(bool update);
			
		private:
			QSharedDataPointer<PerceptionAtomPrivate> d;
	};
}

Q_DECLARE_METATYPE(GluonEngine::PerceptionAtom)
Q_DECLARE_METATYPE(GluonEngine::PerceptionAtom*)

#endif
