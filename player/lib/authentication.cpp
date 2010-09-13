#include "authentication.h"
#include "atticamanager.h"
#include <core/singleton.h>

#include <QDebug>

using namespace GluonPlayer;

template<> GLUON_PLAYER_EXPORT Authentication *GluonCore::Singleton<Authentication>::m_instance = 0;

Authentication::Authentication()
{
}

Authentication::~Authentication()
{
}

QString Authentication::username()
{
    if (AtticaManager::instance()->isProviderValid()) {
        QString temp;
        AtticaManager::instance()->provider().loadCredentials(m_username, temp);
    }
    return m_username;
}

void Authentication::setCredentials(const QString &username, const QString &password)
{
    AtticaManager::instance()->provider().saveCredentials(username, password);
    m_username = username;
}


#include "authentication.moc"
