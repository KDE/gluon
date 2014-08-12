#include <QDebug>
 
#include <player/serviceprovider.h>
#include <attica/provider.h>

#include "selfuser.h"
#include "xmppclient.h"

SelfUser::SelfUser()
{
    m_loggedIn = false;
    
    //login logout
    connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(loginFinished()), SLOT(loginDone()) );
    connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(loginFailed(QString)), SLOT(loginFailed()) );
    
    //registration
    connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(registrationFinished()), SLOT(registrationComplete()) );
    connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(registrationFailed(int)), SLOT(registrationFailed(int)) );
}
 
SelfUser::~SelfUser()
{
}

void SelfUser::setUsername(QString username)
{
    m_username = username;
    emit usernameChanged();
}

QString SelfUser::username()
{
    return m_username;
}

void SelfUser::doLogin(QString m_username, QString m_password)
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
 
void SelfUser::doLogout()
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
 
void SelfUser::loginDone()
{
    m_loggedIn = true;
    emit loginCompleted();
}

void SelfUser::logoutDone()
{
    qDebug() << "logout done!";
    //clearing username
    setUsername("");
    m_loggedIn = false;
    
    emit logoutCompleted();
}
 
void SelfUser::loginFailed()
{
    emit loginFail();
    //clearing username
    setUsername("");
}

void SelfUser::addUser(QString login, QString password, QString password2, QString firstname, QString lastname, QString email)
{       
        //check if all mandatory fields are not empty
    if( login.isEmpty() || password.isEmpty() || password2.isEmpty() || firstname.isEmpty() || lastname.isEmpty() || email.isEmpty() )
    {
                return;
    }
    
    //check if passwords are the same
        if(password != password2){
                return;
        }
    
    GluonPlayer::ServiceProvider::instance()->registerAccount( login, password, email, firstname, lastname );
}
 
void SelfUser::registrationComplete()
{
        emit registrationProcessCompleted("Registration succeeded.");
        return;
}
 
void SelfUser::registrationFailed(int errorcode)
{
        QString hint;
        
        switch( errorcode )
        {
            case 100:
                hint = tr( "Registration succeeded." );
                break;
            case 101:
                hint = tr( "Specify all mandatory fields." );
            case 102:
                hint = tr( "Invalid password." );
                break;
            case 103:
                hint = tr( "Invalid username." );
                break;
            case 104:
                hint = tr( "Username is already taken." );
                break;
            case 105:
                hint = tr( "Email address is already taken." );
                break;
            case 106:
                hint = tr( "Email address is invalid." );
            default:
                hint = tr( "Failed to register new account." );
                break;
        }
        emit registrationProcessCompleted(hint);
        return;
}
