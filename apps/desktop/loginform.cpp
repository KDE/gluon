#include <QDebug>
 
#include <player/serviceprovider.h>
#include <attica/provider.h>

#include "loginform.h"

LoginForm::LoginForm()
{
        m_loggedIn = false;
        
    connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(loginFinished()), SLOT(loginDone()) );
    connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(loginFailed(QString)), SLOT(loginFailed()) );
}
 
LoginForm::~LoginForm()
{
}

void LoginForm::setUsername(QString username)
{
    m_username = username;
}

QString LoginForm::username()
{
    return m_username;
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
    
    setUsername(m_username);
    
    GluonPlayer::ServiceProvider::instance()->login( m_username, m_password );
    // Note: the login result should be checked
}
 
void LoginForm::doLogout()
{
    if( m_loggedIn == false ){
        qDebug() << "not logged in yet?";
        return;
    }
 
    if (GluonPlayer::ServiceProvider::instance()->logout()){
        logoutDone();
        //clearing username
        setUsername("");
    }
    // Note: the login result should be checked
}
 
void LoginForm::loginDone()
{
    m_loggedIn = true;
    emit loginCompleted();
}

void LoginForm::logoutDone()
{
    qDebug() << "logout done!";
    //clearing username
    setUsername("");
    
    emit logoutCompleted();
}
 
void LoginForm::loginFailed()
{
    emit loginFail();
    //clearing username
    setUsername("");
}
  
