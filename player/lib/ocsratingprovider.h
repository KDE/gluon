/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#ifndef GLUONPLAYER_OCSRATINGPROVIDER_H
#define GLUONPLAYER_OCSRATINGPROVIDER_H

#include <QtCore/QObject>

#include "gluon_player_export.h"

namespace Attica
{
    class Provider;
    class BaseJob;
}

namespace GluonPlayer
{

    class GLUON_PLAYER_EXPORT OcsRatingProvider : public QObject
    {

            Q_OBJECT
        public:
            OcsRatingProvider( Attica::Provider* provider, const QString& id, uint rating,
                               QObject* parent = 0 );
            virtual ~OcsRatingProvider();
        private:
            class Private;
            Private* const d;
        Q_SIGNALS:
            void finished( const QString &id );
            void failed( const QString &id );
        private Q_SLOTS:
            void startRatingUpload();
            void ratingUploadComplete( Attica::BaseJob* baseJob );

            friend class OcsProvider;
    };

}

#endif // GLUONPLAYER_OCSRATINGPROVIDER_H
