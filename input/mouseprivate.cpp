#include "mouseprivate.h"

using namespace GluonInput;

MousePrivate::MousePrivate()
{
}

MousePrivate::MousePrivate(MousePrivate &other)
	: QSharedData(other),
	m_originalPosition(other.m_originalPosition),
	m_position(other.m_position),
	m_sensibility(other.m_sensibility)
{
}