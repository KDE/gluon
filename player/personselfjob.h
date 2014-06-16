 
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
 
#ifndef GLUON_PLAYER_PERSONSELFJOB_H
#define GLUON_PLAYER_PERSONSELFJOB_H
 
#include "personself.h"
#include "abstractsocialservicesjob.h"
 
#include <QtCore/QList>
#include <QtCore/QMetaType>
 
namespace Attica
{
    class Provider;
    class BaseJob;
}
 
namespace GluonPlayer
{
    class PersonSelfJob : public AbstractSocialServicesJob
    {
            Q_OBJECT
        public:
            explicit PersonSelfJob( Attica::Provider* provider, QObject* parent = 0 );
            virtual ~PersonSelfJob();
 
            virtual QVariant data();
                        
                        void start();
 
        protected Q_SLOTS:
            virtual void startSocialService();
 
        private Q_SLOTS:
            void processFetchedPersonSelf( Attica::BaseJob* job );
 
        private:
            class Private;
            Private* const d;
    };
}
 
Q_DECLARE_METATYPE( GluonPlayer::PersonSelf* )
 
#endif // GLUON_PLAYER_PERSONSELFJOB_H