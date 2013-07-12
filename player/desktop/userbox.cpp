
#include "userbox.h"

#include <player/lib/serviceprovider.h>
#include <player/lib/personselfjob.h>

#include <KDE/KLocale>
#include <KDE/KLocalizedString>
#include <KDE/KDebug>
#include <QString>
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
	kDebug() << "loadedUserData";
	QVariant userData = job->data();
	GluonPlayer::PersonSelf* castedData = userData.value<GluonPlayer::PersonSelf*>();
	
	setUsername(castedData->id());
	setFirstname(castedData->firstName());
	setLastname(castedData->lastName());
}

void UserBox::setUsername(QString str)
{
	m_username = str;
}

void UserBox::setFirstname(QString str)
{
	m_firstname = str;
}

void UserBox::setLastname(QString str)
{
	m_lastname = str;
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
