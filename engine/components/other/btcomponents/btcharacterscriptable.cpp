#include "btcharacterscriptable.h"

#include "character.h"
#include <engine/gameobject.h>

using namespace GluonEngine;

btCharacterScriptable::btCharacterScriptable(QObject * parent)
	: btCharacter()
    , m_time(0)
{
    this->setParent(parent);
}

btCharacterScriptable::~btCharacterScriptable()
{
}

QVector3D btCharacterScriptable::position() const
{
    Character * character = qobject_cast< Character* >(this->parent());
    return character->gameObject()->position();
}

void btCharacterScriptable::setPosition(const QVector3D& newPosition)
{
    Character * character = qobject_cast< Character* >(this->parent());
    character->gameObject()->setPosition(newPosition);
}

QQuaternion btCharacterScriptable::orientation() const
{
    Character * character = qobject_cast< Character* >(this->parent());
    return character->gameObject()->orientation();
}

void btCharacterScriptable::setOrientation(const QQuaternion& newOrientation)
{
    Character * character = qobject_cast< Character* >(this->parent());
    character->gameObject()->setOrientation(newOrientation);
}

btPerception* btCharacterScriptable::perception()
{
    return btCharacter::perception();
}

int btCharacterScriptable::time()
{
    return m_time;
}

void btCharacterScriptable::setTime(int time)
{
    m_time = time;
}

#include "btcharacterscriptable.moc"

