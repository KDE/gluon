#include "atticamanager.h"

using namespace GluonPlayer;

template<> AtticaManager* GluonCore::Singleton<AtticaManager>::m_instance = 0;

AtticaManager::AtticaManager()
{
    connect( &m_manager, SIGNAL( defaultProvidersLoaded() ), SLOT( providersUpdated() ) );
    m_manager.loadDefaultProviders();
}

AtticaManager::~AtticaManager()
{
}

bool AtticaManager::isProviderValid()
{
    return m_provider.isValid();
}

Attica::Provider AtticaManager::provider()
{
    return m_provider;
}

void AtticaManager::providersUpdated()
{
    if( !m_manager.providers().isEmpty() )
    {
        m_provider = m_manager.providerByUrl( QUrl( "https://api.opendesktop.org/v1/" ) );
        if( !m_provider.isValid() )
        {
            emit failedToFetchProvider();
        }
        else
        {
            emit gotProvider();
        }
    }
}

#include "atticamanager.moc"

