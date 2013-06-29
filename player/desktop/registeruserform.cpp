#include "registeruserform.h"

#include <player/lib/serviceprovider.h>
#include <KDebug>


RegisterUserForm::RegisterUserForm()
{
	connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(registrationFinished()), SLOT(registrationComplete()) );
    connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(registrationFailed(int)), SLOT(registrationFailed(int)) );
}

RegisterUserForm::~RegisterUserForm()
{
}

void RegisterUserForm::addUser(QString login, QString password, QString password2, QString firstname, QString lastname, QString email)
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

void RegisterUserForm::registrationComplete()
{
	emit registrationProcessCompleted("Registration succeeded.");
	return;
}

void RegisterUserForm::registrationFailed(int errorcode)
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
