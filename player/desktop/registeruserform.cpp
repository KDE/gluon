#include "registeruserform.h"

#include <player/lib/serviceprovider.h>
#include <KDebug>


RegisterUserForm::RegisterUserForm()
{	
}

RegisterUserForm::~RegisterUserForm()
{
}

void RegisterUserForm::addUser(QString login, QString password, QString password2, QString firstname, QString lastname, QString email)
{
	
	kDebug() << email;
	
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
