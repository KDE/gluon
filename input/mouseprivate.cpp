#include "mouseprivate.h"

using namespace GluonInput;

MousePrivate::MousePrivate()
{
}

MousePrivate::MousePrivate(MousePrivate &other)
        : QSharedData(other),
        originalPosition(other.originalPosition),
        position(other.position),
        sensibility(other.sensibility)
{
}