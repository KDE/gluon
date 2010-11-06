#include "authentication.h"
#include "atticamanager.h"
#include <attica/postjob.h>
#include <core/singleton.h>

#include <QDebug>

using namespace GluonPlayer;

template<> GLUON_PLAYER_EXPORT Authentication* GluonCore::Singleton<Authentication>::m_instance = 0;

Authentication::Authentication() : m_initialized( false ), m_loggedIn( false )
{
}

Authentication::~Authentication()
{
}

void Authentication::init()
{
    if( !AtticaManager::instance()->isProviderValid() )
    {
        connect( AtticaManager::instance(), SIGNAL( gotProvider() ), SLOT( finishInit() ) );
        connect( AtticaManager::instance(), SIGNAL( failedToFetchProvider() ), SIGNAL( initFailed() ) );
    }
}

bool Authentication::isInitialized()
{
    return m_initialized;
}

QString Authentication::username()
{
    return m_username;
}

QString Authentication::password()
{
    return m_password;
}

bool Authentication::login( const QString& username, const QString& password )
{
    m_username = username;
    m_password = password;

    if( AtticaManager::instance()->isProviderValid() )
    {
        m_checkLoginJob = AtticaManager::instance()->provider().checkLogin( m_username, m_password );
        connect( m_checkLoginJob, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( checkLoginResult( Attica::BaseJob* ) ) );
        m_checkLoginJob->start();
        return true;
    }

    return false;
}

bool Authentication::isLoggedIn()
{
    return m_loggedIn;
}

bool Authentication::hasCredentials()
{
    return AtticaManager::instance()->provider().hasCredentials();
}

void Authentication::finishInit()
{
    AtticaManager::instance()->provider().loadCredentials( m_username, m_password );
    m_initialized = true;
    emit initialized();
}

void Authentication::checkLoginResult( Attica::BaseJob* baseJob )
{
    Attica::PostJob* job = qobject_cast<Attica::PostJob*>( baseJob );

    if( job->metadata().error() == Attica::Metadata::NoError )
    {
        AtticaManager::instance()->provider().saveCredentials( m_username, m_password );
        m_loggedIn = true;
        emit loggedIn();
    }
    else
    {
        m_loggedIn = false;
        emit loginFailed();
    }
}

#include "authentication.moc"
