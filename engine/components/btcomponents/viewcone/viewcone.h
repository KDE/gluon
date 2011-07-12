#ifndef VIEWCONE_H
#define VIEWCONE_H

#include <engine/gluon_engine_export.h>
#include <QtCore/QObject>
#include <engine/component.h>

namespace BehaviorTree
{
	class ViewConePrivate;
	
        class GLUON_COMPONENT_BTVIEWCONE_EXPORT ViewCone : public GluonEngine::Component
	{
		Q_OBJECT
		GLUON_OBJECT(BehaviorTree::ViewCone)
		Q_INTERFACES(GluonEngine::Component)
		Q_PROPERTY(qreal offsetAngleHorizontal READ offsetAngleHorizontal WRITE setOffsetAngleHorizontal);
		Q_PROPERTY(qreal offsetAngleVertical READ offsetAngleVertical WRITE setOffsetAngleVertical);
		Q_PROPERTY(qreal extentAngleHorizontal READ extentAngleHorizontal WRITE setExtentAngleHorizontal);
		Q_PROPERTY(qreal extentAngleVertical READ extentAngleVertical WRITE setExtentAngleVertical);
		Q_PROPERTY(qreal radius READ radius WRITE setRadius);
		Q_PROPERTY(qreal knowledgePrecision READ knowledgePrecision WRITE setKnowledgePrecision);
		
		public:
			ViewCone(QObject * parent = 0);
			ViewCone(const ViewCone& other, QObject* parent = 0);
			~ViewCone();
			
			virtual void initialize();
			
			qreal offsetAngleHorizontal() const;
			void setOffsetAngleHorizontal(qreal value);
			
			qreal offsetAngleVertical() const;
			void setOffsetAngleVertical(qreal value);
			
			qreal extentAngleHorizontal() const;
			void setExtentAngleHorizontal(qreal value);
			
			qreal extentAngleVertical() const;
			void setExtentAngleVertical(qreal value);
			
			qreal radius() const;
			void setRadius(qreal value);
			
			qreal knowledgePrecision() const;
			void setKnowledgePrecision(qreal value);
			
		private:
			QSharedDataPointer<ViewConePrivate> d;
	};
}

Q_DECLARE_METATYPE(BehaviorTree::ViewCone)
Q_DECLARE_METATYPE(BehaviorTree::ViewCone*)

#endif
