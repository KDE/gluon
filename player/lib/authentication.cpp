#include "authentication.h"
#include "atticamanager.h"
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

void Authentication::onRegisterClicked( const QString& username, const QString& password, const QString& mail,
                                            const QString& firstName, const QString& lastName)
{
    // here we assume that all data has been checked in onRegisterDataChanged()

    if( AtticaManager::instance()->isProviderValid() )
    {
        m_registerJob = AtticaManager::instance()->provider().registerAccount(username, password, mail, firstName, lastName);
        connect(m_registerJob, SIGNAL(finished(Attica::BaseJob*)), SLOT(onRegisterAccountFinished(Attica::BaseJob*)));
        m_registerJob->start();
    }
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

void Authentication::showRegisterError(const Attica::Metadata& metadata)
{
    if (metadata.error() == Attica::Metadata::NetworkError) {
        qWarning() << tr("Failed to register new account.");
    } else {
        /*
# 100 - successful / valid account
# 101 - please specify all mandatory fields
# 102 - please specify a valid password
# 103 - please specify a valid login
# 104 - login already exists
# 105 - email already taken
*/
        // TODO: Looks like more correct place for this stuff is in libattica,
        // for example metadata().statusString() or smth like that.
        // So here will be only showRegisterHint("dialog-close", statusString);
        // no switch.
        QWidget* widgetToHighlight = 0;
        QString hint;
        switch (metadata.statusCode()) {
            case 100:
                hint = tr("Registration succeeded.");
                break;
            case 101:
                hint = tr("Failed to register new account: please specify all mandatory fields.");
            case 102:
                hint = tr("Failed to register new account: invalid password.");
                break;
            case 103:
                hint = tr("Failed to register new account: invalid username.");
                break;
            case 104:
                hint = tr("Failed to register new account: the requested username is already taken.");
                break;
            case 105:
                hint = tr("Failed to register new account: the specified email address is already taken.");
                break;
            case 106:
                hint = tr("Failed to register new account: the specified email address is invalid.");
            default:
                hint = tr("Failed to register new account.");
                break;
        }
        qDebug() << hint;
    }
}

void Authentication::onRegisterAccountFinished(Attica::BaseJob* job)
{
    Attica::PostJob* postJob = static_cast<Attica::PostJob*>(job);

    if (postJob->metadata().error() == Attica::Metadata::NoError)
    {
        AtticaManager::instance()->provider().saveCredentials( m_username, m_password );
        emit registered();
    }
    else
    {
        // Note: It is worth to invoke this error status later
        // qDebug() << "register error:" << postJob->metadata().error() << "statusCode:" << postJob->metadata().statusCode();
        showRegisterError( postJob->metadata() );
    }
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
