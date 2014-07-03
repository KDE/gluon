/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
 * Copyright (C) 2011 Laszlo Papp <lpapp@kde.org>
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

#ifndef GLUON_PLAYER_DECLINEFRIENDJOB_H
#define GLUON_PLAYER_DECLINEFRIENDJOB_H

#include "abstractsocialservicesjob.h"

#include "gluon_player_export.h"

namespace Attica
{
    class Provider;
    class BaseJob;
}

namespace GluonPlayer
{
    class GLUON_PLAYER_EXPORT DeclineFriendJob : public AbstractSocialServicesJob
    {
            Q_OBJECT
        public:
            DeclineFriendJob( Attica::Provider* provider, const QString& to, QObject* parent = 0);
            virtual ~DeclineFriendJob();
            
            virtual QVariant data();

        protected Q_SLOTS:
            virtual void startSocialService( );

        private Q_SLOTS:
            void declineFriendComplete( Attica::BaseJob* baseJob );
            
        private:
            class Private;
            Private* const d;
    };
}

#endif // GLUON_PLAYER_DECLINEFRIENDJOB_H
