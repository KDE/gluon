 
#include <QDebug>
 
#include <player/serviceprovider.h>
#include <player/addfriendjob.h>
#include <attica/provider.h>

#include "singleuser.h"

SingleUser::SingleUser()
{
    //setting to default that this is not self's friend
    m_username = "nd";
    m_name = "nd";
    m_surname = "nd";
    isFriend = false;
        
    //connect( GluonPlayer::ServiceProvider::instance(), SIGNAL(loginFinished()), SLOT(loginDone()) );
}
 
SingleUser::~SingleUser()
{
}

void SingleUser::addFriend()
{
    GluonPlayer::AddFriendJob * job = GluonPlayer::ServiceProvider::instance()->addFriend(m_username);
    connect(job, SIGNAL(succeeded()), SIGNAL(friendRequestSent()));
    connect(job, SIGNAL(failed()), SIGNAL(friendRequestFailed()));
    job->start();
}

QString SingleUser::username() const
{
    return m_username;
}

QString SingleUser::name() const
{
    return m_name;
}

QString SingleUser::surname() const
{
    return m_surname;
}

//when id is set, load everything
void SingleUser::setUsername(const QString &username)
{
    m_username = username;
    emit usernameChanged();
}

void SingleUser::setName(const QString &name)
{
    m_name = name;
    emit nameChanged();
}

void SingleUser::setSurname(const QString &surname)
{
    m_surname = surname;
    emit surnameChanged();
}