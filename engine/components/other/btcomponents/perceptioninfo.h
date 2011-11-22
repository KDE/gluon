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

#ifndef PERCEPTIONINFO_H
#define PERCEPTIONINFO_H

#include <QtCore/QObject>
#include <QtCore/QSharedData>

#include "engine/gluon_engine_export.h"
#include "engine/component.h"
#include "engine/asset.h"

class QVector3D;
class btPerceptionInfo;
class QScriptValue;
class QScriptEngine;

namespace GluonEngine
{
    class PerceptionInfoPrivate;

    class BTCOMPONENT_EXPORT PerceptionInfo : public GluonEngine::Component
    {
            Q_OBJECT
            GLUON_OBJECT( GluonEngine::PerceptionInfo )
            Q_INTERFACES( GluonEngine::Component )
            Q_PROPERTY( QVector3D position READ position WRITE setPosition/* NOTIFY positionUpdated*/ )
            Q_PROPERTY( qreal radius READ radius WRITE setRadius/* NOTIFY radiusUpdated*/ )
            Q_PROPERTY( GluonEngine::Asset* script READ script WRITE setScript )

        public:
            PerceptionInfo( QObject* parent = 0 );
            PerceptionInfo( const PerceptionInfo& other, QObject* parent = 0 );
            ~PerceptionInfo();

            QVector3D position() const;
            void setPosition( const QVector3D& newPosition );

            qreal radius() const;
            void setRadius( const qreal& newRadius );

            btPerceptionInfo* getBtPerceptionInfo();

            virtual void initialize();
            virtual void start();
            virtual void update( int elapsedMilliseconds );
            virtual void draw( int timeLapse = 0 );
            virtual void stop();
            virtual void cleanup();

            virtual GluonEngine::Asset* script();

            virtual QVariant getAdjustedValue( qreal precision );

        public slots:
            virtual void setScript( GluonEngine::Asset* asset );

        signals:
            Q_INVOKABLE void infoUpdated();

        private:
            QSharedDataPointer<PerceptionInfoPrivate> d;
    };
}

Q_DECLARE_METATYPE( GluonEngine::PerceptionInfo )
Q_DECLARE_METATYPE( GluonEngine::PerceptionInfo* )

#endif
