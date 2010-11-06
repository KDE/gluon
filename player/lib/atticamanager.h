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
             * @return true if provider is valid, false if otherwise
             */
            bool isProviderValid();
            /**
             * Can be used to access the Attica provider.
             * @return The Attica provider
             */
            Attica::Provider provider();

        private:
            friend class GluonCore::Singleton<AtticaManager>;
            AtticaManager();
            ~AtticaManager();
            Q_DISABLE_COPY( AtticaManager )

            Attica::ProviderManager m_manager;
            Attica::Provider m_provider;

        private slots:
            void providersUpdated();

        signals:
            /**
             * signal which is emitted when a provider has been loaded
             */
            void gotProvider();
            /**
             * signal which is emitted when provider failed to loaded
             */
            void failedToFetchProvider();
    };
}

#endif // ATTICAMANAGER_H
