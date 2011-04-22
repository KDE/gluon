/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef ATTICAMANAGER_H
#define ATTICAMANAGER_H

#include <core/singleton.h>

#include <attica/providermanager.h>

namespace GluonPlayer
{
    /**
     *\brief Class which helps gluon libraries to access Attica
     *
     * This class helps gluon libraries to access Attica so that
     * collaboration actions can be performed.
     *
     * \note This should <b>not</b> be used in code outside GluonPlayer library.
     * Use the appropriate classes instead.
     */

    class AtticaManager : public GluonCore::Singleton<AtticaManager>
    {
            Q_OBJECT

        public:
            /**
             * Used to check if we have loaded a valid OCS provider
             * @return true if provider is valid, false otherwise
             */
            bool isProviderValid();
            /**
             * Can be used to access the Attica provider.
             * @return The Attica provider
             */
            Attica::Provider provider();

            bool downloadGame( const QString& id );

        protected Q_SLOTS:
            void providersUpdated();
            void requestContent();
            void processFetchedGameDetails( Attica::BaseJob* job );

        Q_SIGNALS:
            /**
             * signal which is emitted when a provider has been loaded
             */
            void gotProvider();
            /**
             * signal which is emitted when provider failed to loaded
             */
            void failedToFetchProvider();

        private:
            friend class GluonCore::Singleton<AtticaManager>;
            AtticaManager();
            ~AtticaManager();
            Q_DISABLE_COPY( AtticaManager )

            Attica::ProviderManager m_manager;
            Attica::Provider m_provider;
            bool isDownloading;
            QString m_currentId;
    };
}

#endif // ATTICAMANAGER_H
