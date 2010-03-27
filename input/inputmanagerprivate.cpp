#include "inputmanagerprivate.h"

using namespace GluonInput;

InputManagerPrivate::InputManagerPrivate()
{
}

InputManagerPrivate::InputManagerPrivate(InputManagerPrivate &other)
	: QSharedData(other),
	m_instance(other.m_instance)
{
}
