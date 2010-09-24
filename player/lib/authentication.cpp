#include "authentication.h"
#include "atticamanager.h"
#include <attica/postjob.h>
#include <core/singleton.h>

#include <QDebug>

using namespace GluonPlayer;

template<> GLUON_PLAYER_EXPORT Authentication *GluonCore::Singleton<Authentication>::m_instance = 0;

Authentication::Authentication() : m_loggedIn(false)
{
}

Authentication::~Authentication()
{
}

QString Authentication::username()
{
    if (m_loggedIn) {
        return m_username;
    }
    return QString();
}

void Authentication::login(const QString &username, const QString &password)
{
    m_username = username;
    m_password = password;

    if (AtticaManager::instance()->isProviderValid()) {
        checkAndPerformLogin();
    } else {
        connect(AtticaManager::instance(), SIGNAL(gotProvider()), SLOT(checkAndPerformLogin()));
        connect(AtticaManager::instance(), SIGNAL(failedToFetchProvider()), SIGNAL(loginFailed()));
    }
}

bool Authentication::isLoggedIn()
{
    return m_loggedIn;
}

void Authentication::checkAndPerformLogin()
{
    m_checkLoginJob = AtticaManager::instance()->provider().checkLogin(m_username, m_password);
    connect(m_checkLoginJob, SIGNAL(finished(Attica::BaseJob*)), SLOT(performLogin(Attica::BaseJob*)));
    m_checkLoginJob->start();
}

void Authentication::performLogin(Attica::BaseJob *baseJob)
{
    Attica::PostJob *job = qobject_cast<Attica::PostJob*>(baseJob);

    if (job->metadata().error() == Attica::Metadata::NoError) {
        AtticaManager::instance()->provider().saveCredentials(m_username, m_password);
        m_loggedIn = true;
        emit loggedIn();
    } else {
        m_loggedIn = false;
        emit loginFailed();
    }
}

#include "authentication.moc"
