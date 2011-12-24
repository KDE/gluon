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

#ifndef GLUONPLAYER_EDITGAMEJOB_H
#define GLUONPLAYER_EDITGAMEJOB_H

#include "abstractsocialservicesjob.h"

namespace Attica
{
    class Provider;
    class BaseJob;
}

namespace GluonPlayer
{
    class EditGameJob : public AbstractSocialServicesJob
    {
            Q_OBJECT

        public:
            EditGameJob( Attica::Provider* provider, const QString& id, QObject* parent = 0 );
            virtual ~EditGameJob();

            virtual QVariant data();

            void setCategory( const QString& categoryId );
            void setName( const QString& name );
            void setVersion( const QString& version );
            void setDescription( const QString& description );
            void setChangelog( const QString& changelog );
            void setLicense( const QString& licenseId );
            void setHomepage( const QString& homepage );
            void setDownloadType( const QString& downloadType );
            void setDownloadPrice( const QString& downloadPrice );
            void setDownloadLink( const QString& downloadLink );
            void setDownloadName( const QString& downloadName );

        Q_SIGNALS:
            void fetchedExistingGame( const QString& id );

        protected Q_SLOTS:
            virtual void startSocialService();

        private Q_SLOTS:
            void startFetchingExistingGame();
            void processFetchedGameDetails( Attica::BaseJob* job );
            void editingComplete( Attica::BaseJob* job );
            void startEditionUpload();

            void applyName();
            void applyVersion();
            void applyDescription();
            void applyCategory();
            void applyChangelog();
            void applyLicense();
            void applyHomepage();
            void applyDownloadType();
            void applyDownloadPrice();
            void applyDownloadLink();
            void applyDownloadName();

        private:
            class Private;
            Private* const d;
    };
}

#endif // GLUONPLAYER_EDITGAMEJOB_H
