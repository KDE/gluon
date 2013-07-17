
#include "userbox.h"

#include <player/lib/serviceprovider.h>
#include <player/lib/personselfjob.h>

#include <KDE/KLocale>
#include <KDE/KLocalizedString>
#include <KDE/KDebug>
#include <QString>
#include <QDebug>
#include <attica/provider.h>

/**
 * When this object is created it collects all user info, 
 * ready to be displayed.
 */
UserBox::UserBox()
{
	//when attica is ready, just change content
	connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(initializationFinished()), SLOT(loadUserData()) );
	
	//if the user perfor a login during use session of gluon player, userbox will be notified
	connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(loginFinished()), SLOT(loadUserData()) );
	
	//loogut case
	connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(logoutFinished()), SLOT(logoutDone()) );
}

void UserBox::loadUserData()
{
	//as the object is instantiated, get info
	GluonPlayer::PersonSelfJob* job = GluonPlayer::ServiceProvider::instance()->personSelf();
	if ( job != NULL ){
		connect(job, SIGNAL(succeeded()), this, SLOT(loadedUserData()) );
		connect(job, SIGNAL(failed()), this, SLOT(loadedUserDataFailed()) );
		job->start();
	}
}

void UserBox::loadedUserData()
{
	GluonPlayer::PersonSelfJob* job = qobject_cast<GluonPlayer::PersonSelfJob*>(QObject::sender());
	
	QVariant userData = job->data();
	GluonPlayer::PersonSelf* castedData = userData.value<GluonPlayer::PersonSelf*>();
	
	m_username = castedData->id();
	m_firstname = castedData->firstName();
	m_lastname = castedData->lastName();
	
	emit dataLoaded();
}

/**
 * If OCS request fails it means user must authenticate.
 */
void UserBox::loadedUserDataFailed()
{
	emit needsAuthentication();
}

/**
 * This function simply returns the username of user currently logged.
 */
QString UserBox::username()
{
	return m_username;
}

QString UserBox::firstname()
{
	return m_firstname;
}

QString UserBox::lastname()
{
	return m_lastname;
}

void UserBox::logout()
{
	GluonPlayer::ServiceProvider::instance()->logout();
}

void UserBox::logoutDone()
{
	emit logoutFinished();
}

UserBox::~UserBox()
{
}
