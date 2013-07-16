
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
	connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(initializationFinished()), SLOT(loadUserData()) );
	
	//as the object is instantiated, get info
	loadUserData();
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
	qDebug() << "loaded1";
	GluonPlayer::PersonSelfJob* job = qobject_cast<GluonPlayer::PersonSelfJob*>(QObject::sender());
	
	QVariant userData = job->data();
	GluonPlayer::PersonSelf* castedData = userData.value<GluonPlayer::PersonSelf*>();
	
	m_username = castedData->id();
	m_firstname = castedData->firstName();
	m_lastname = castedData->lastName();
	
	emit dataLoaded();
	qDebug() << "loaded2";
}

/**
 * If OCS request fails it means user must authenticate.
 */
void UserBox::loadedUserDataFailed()
{
	GluonPlayer::PersonSelfJob* job = qobject_cast<GluonPlayer::PersonSelfJob*>(QObject::sender());
	
	QVariant userData = job->data();
	QString errorText = job->errorText();
	
	qDebug() << "OCS error: " << errorText;
	
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

UserBox::~UserBox()
{
}
