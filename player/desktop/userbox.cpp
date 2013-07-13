
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
	m_username = "loading...";
	m_firstname = "loading...";
	m_lastname = "loading...";
	
	//as the object is instantiated, get info
	job = GluonPlayer::ServiceProvider::instance()->personSelf();
	connect(job, SIGNAL(finished()), this, SLOT(loadedUserData()));
	job->start();
}

void UserBox::loadedUserData()
{
	QVariant userData = job->data();
	GluonPlayer::PersonSelf* castedData = userData.value<GluonPlayer::PersonSelf*>();
	
	m_username = castedData->id();
	m_firstname = castedData->firstName();
	m_lastname = castedData->lastName();
	
	emit dataLoaded();
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
