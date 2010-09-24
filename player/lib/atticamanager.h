#ifndef ATTICAMANAGER_H
#define ATTICAMANAGER_H

#include <core/singleton.h>
#include <attica/providermanager.h>

namespace GluonPlayer
{
    class AtticaManager : public GluonCore::Singleton<AtticaManager>
    {
        Q_OBJECT

        public:
            bool isProviderValid();
            Attica::Provider provider();

        private:
            friend class GluonCore::Singleton<AtticaManager>;
            AtticaManager();
            ~AtticaManager();
            Q_DISABLE_COPY(AtticaManager)

            Attica::ProviderManager m_manager;
            Attica::Provider m_provider;

        private slots:
            void providersUpdated();

        signals:
            void gotProvider();
            void failedToFetchProvider();
    };
}

#endif // ATTICAMANAGER_H
