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

#ifndef PERCEPTIONATOM_H
#define PERCEPTIONATOM_H

#include <QtCore/QObject>
#include <QtCore/QSharedData>

#include "engine/gluon_engine_export.h"
#include "engine/component.h"
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
