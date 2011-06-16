#ifndef PERCEPTIONINFO_H
#define PERCEPTIONINFO_H

#include "bt_export.h"

#include <QtCore/QObject>
#include <engine/component.h>
#include <QtCore/QSharedData>
#include <engine/asset.h>

class QVector3D;
class btPerceptionInfo;
class QScriptValue;
class QScriptEngine;

namespace BehaviorTree
{
	class PerceptionInfoPrivate;
	
	class BTCOMPONENT_EXPORT PerceptionInfo : public GluonEngine::Component
	{
		Q_OBJECT
		GLUON_OBJECT(BehaviorTree::PerceptionInfo)
		Q_INTERFACES(GluonEngine::Component)
                Q_PROPERTY(QVector3D position READ position WRITE setPosition/* NOTIFY positionUpdated*/)
                Q_PROPERTY(qreal radius READ radius WRITE setRadius/* NOTIFY radiusUpdated*/)
		Q_PROPERTY(GluonEngine::Asset* script READ script WRITE setScript)
        
		public:
			PerceptionInfo(QObject* parent = 0);
			PerceptionInfo(const PerceptionInfo& other, QObject* parent = 0);
			~PerceptionInfo();
			
			QVector3D position() const;
			void setPosition(const QVector3D& newPosition);
        
			qreal radius() const;
			void setRadius(const qreal& newRadius);
			
			btPerceptionInfo * getBtPerceptionInfo();
			
			virtual void initialize();
            virtual void start();
            virtual void update(int elapsedMilliseconds);
            virtual void draw(int timeLapse = 0);
            virtual void stop();
            virtual void cleanup();
			
			virtual GluonEngine::Asset* script();
			
			virtual QVariant getAdjustedValue(qreal precision);

        public slots:
            virtual void setScript(GluonEngine::Asset* asset);
			
		signals:
			Q_INVOKABLE void infoUpdated();

		private:
			QSharedDataPointer<PerceptionInfoPrivate> d;
	};
}

Q_DECLARE_METATYPE(BehaviorTree::PerceptionInfo)
Q_DECLARE_METATYPE(BehaviorTree::PerceptionInfo*)

#endif
