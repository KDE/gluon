/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2009 Dan Leinir Turthra Jensen <admin@leinir.dk>
 * Copyright (c) 2009 Kim Jung Nissen <jungnissen@gmail.com>
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

#ifndef GLUON_SMARTS_BTPERCEPTIONINFO_H
#define GLUON_SMARTS_BTPERCEPTIONINFO_H

#include <core/gluonvarianttypes.h>

#include <QtCore/QVariant>

namespace GluonSmarts
{
    class btPerceptionInfo : public QObject
    {
            Q_OBJECT
            Q_PROPERTY( Eigen::Vector3f position READ position WRITE setPosition NOTIFY positionUpdated )
            Q_PROPERTY( qreal radius READ radius WRITE setRadius NOTIFY radiusUpdated )

        public:
            btPerceptionInfo( QObject* parent );
            virtual ~btPerceptionInfo();

            virtual Eigen::Vector3f position() const;
            virtual void setPosition( const Eigen::Vector3f& newPosition );

            virtual qreal radius() const;
            virtual void setRadius( const qreal& newRadius );

            virtual QVariant getAdjustedValue( qreal precision ) const = 0;

        Q_SIGNALS:
            void infoUpdated();
            void positionUpdated( Eigen::Vector3f );
            void radiusUpdated( qreal );

        private:
            class btPerceptionInfoPrivate;
            btPerceptionInfoPrivate* d;
    };
}

#endif // GLUON_SMARTS_BTPERCEPTIONINFO_H
