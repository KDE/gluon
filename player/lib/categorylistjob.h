/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#ifndef GLUON_PLAYER_CATEGORYLISTJOB_H
#define GLUON_PLAYER_CATEGORYLISTJOB_H

#include "gluon_player_export.h"

#include "abstractsocialservicesjob.h"

#include <QList>

namespace Attica
{
    class Provider;
    class BaseJob;
}

namespace GluonPlayer
{
    class GLUON_PLAYER_EXPORT CategoryItem : public QObject
    {
            Q_OBJECT
        public:
            CategoryItem( const QString& id, const QString& name, QObject* parent = 0 );
            virtual ~CategoryItem();

            QString id() const;
            QString name() const;

        private:
            class Private;
            Private* const d;
    };

    class CategoryListJob : public AbstractSocialServicesJob
    {
            Q_OBJECT
        public:

            explicit CategoryListJob( Attica::Provider* provider, QObject* parent = 0 );
            virtual ~CategoryListJob();

            virtual QVariant data();

        protected Q_SLOTS:
            virtual void startSocialService();

        private Q_SLOTS:
            void processFetchedCategoryList( Attica::BaseJob* job );

        private:
            class Private;
            Private* const d;
    };
}

#endif // GLUON_PLAYER_CATEGORYLISTJOB_H
