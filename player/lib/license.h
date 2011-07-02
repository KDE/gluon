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

#ifndef GLUONPLAYER_LICENSE_H
#define GLUONPLAYER_LICENSE_H

#include <QtCore/QObject>

#include "gluon_player_export.h"

namespace Attica
{
    class Provider;
    class BaseJob;
}

namespace GluonPlayer
{

    class GLUON_PLAYER_EXPORT LicenseItem : public QObject
    {
            Q_OBJECT
        public:
            explicit LicenseItem( const QString& id, const QString& licenseName, const QString& licenseWebsite,
                                  QObject* parent = 0 );
            virtual ~LicenseItem();

            QString id() const;
            QString licenseName() const;
            QString licenseWebsite() const;

        private:
            class Private;
            Private* const d;
    };

    class License : public QObject
    {
            Q_OBJECT
        public:
            explicit License( Attica::Provider* provider, QObject* parent = 0 );
            virtual ~License();

        private Q_SLOTS:
            void fetchLicenses();
            void processFetchedLicenses( Attica::BaseJob* job );

        Q_SIGNALS:
            void licensesFetched( QList<GluonPlayer::LicenseItem*> licenses );
            void failed();

        private:
            class Private;
            Private* const d;
    };

}

#endif // GLUONPLAYER_LICENSE_H
