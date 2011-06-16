#include "btcharacter.h"

btCharacter::btCharacter()
{
    think = true;
}

btCharacter::~btCharacter()
{

}

void btCharacter::stopThinking()
{
    think = false;
}

void btCharacter::startThinking()
{
    think = true;
}

bool btCharacter::continueThinking()
{
    return think;
}

#include "btcharacter.moc"
