/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <shaan7in@gmail.com>
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

#ifndef GLUONPLAYER_ACTIVITYLISTJOB_H
#define GLUONPLAYER_ACTIVITYLISTJOB_H

#include "abstractsocialservicesjob.h"

#include "models/activityitem.h"
#include "models/personitem.h"

#include <QtCore/QList>
#include <QtCore/QMetaType>

namespace Attica
{
    class BaseJob;
    class Person;
    class Activity;
}

namespace GluonPlayer
{

    class ActivityListJob : public AbstractSocialServicesJob
    {
            Q_OBJECT

        public:
            ActivityListJob( Attica::Provider* provider );
            virtual ~ActivityListJob();

            virtual QVariant data();

        protected Q_SLOTS:
            virtual void startSocialService();

        private Q_SLOTS:
            void processFetchedActivityList( Attica::BaseJob* job );

        private:
            class Private;
            Private* const d;
    };

}

// Q_DECLARE_METATYPE( QList<GluonPlayer::PersonItem*> )

#endif // GLUONPLAYER_ACTIVITYLISTJOB_H
