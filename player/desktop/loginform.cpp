
#include "loginform.h"

#include <player/lib/serviceprovider.h>

#include <KDE/KLocale>
#include <KDE/KLocalizedString>
#include <KDE/KDebug>

#include <attica/provider.h>

#include "mainwindow.h"

LoginForm::LoginForm()
{
	m_loggedIn = false;
	
    connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(loginFinished()), SLOT(loginDone()) );
    connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(loginFailed(QString)), SLOT(loginFailed()) );
}

LoginForm::~LoginForm()
{
}

void LoginForm::doLogin(QString m_username, QString m_password)
{
    if( m_loggedIn )
    {
        doLogout();
        return;
    }

    if( m_username.isEmpty() || m_password.isEmpty() )
    {
        return;
    }
    GluonPlayer::ServiceProvider::instance()->login( m_username, m_password );
    // Note: the login result should be checked
}

void LoginForm::doLogout()
{
    if( m_loggedIn == false )
        return;

    if (GluonPlayer::ServiceProvider::instance()->logout())
        logoutDone();
    // Note: the login result should be checked
}

void LoginForm::loginDone()
{
	emit loginCompleted();
}

void LoginForm::logoutDone()
{
	qDebug() << "logout done!";
}

void LoginForm::loginFailed()
{
    emit loginFail();
}
