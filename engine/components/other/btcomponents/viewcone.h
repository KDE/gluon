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

#ifndef VIEWCONE_H
#define VIEWCONE_H

#include <QtCore/QObject>
#include "engine/gluon_engine_export.h"
#include "engine/component.h"

namespace GluonEngine
{
	class ViewConePrivate;
	
        class BTCOMPONENT_EXPORT ViewCone : public GluonEngine::Component
	{
		Q_OBJECT
                GLUON_OBJECT(GluonEngine::ViewCone)
		Q_INTERFACES(GluonEngine::Component)
		Q_PROPERTY(qreal offsetAngleHorizontal READ offsetAngleHorizontal WRITE setOffsetAngleHorizontal);
		Q_PROPERTY(qreal offsetAngleVertical READ offsetAngleVertical WRITE setOffsetAngleVertical);
		Q_PROPERTY(qreal extentAngleHorizontal READ extentAngleHorizontal WRITE setExtentAngleHorizontal);
		Q_PROPERTY(qreal extentAngleVertical READ extentAngleVertical WRITE setExtentAngleVertical);
		Q_PROPERTY(qreal radius READ radius WRITE setRadius);
		Q_PROPERTY(qreal knowledgePrecision READ knowledgePrecision WRITE setKnowledgePrecision);
		
		public:
                        Q_INVOKABLE ViewCone(QObject * parent = 0);
			ViewCone(const ViewCone& other, QObject* parent = 0);
			~ViewCone();
                        virtual QString category() const;
			
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

Q_DECLARE_METATYPE(GluonEngine::ViewCone)
Q_DECLARE_METATYPE(GluonEngine::ViewCone*)

#endif
