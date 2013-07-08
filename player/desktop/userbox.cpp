
#include "userbox.h"

#include <player/lib/serviceprovider.h>

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
	
}

/**
 * This function simply returns the username of user currently logged.
 */
QString UserBox::username()
{
	return QString("example");
}

UserBox::~UserBox()
{
}
