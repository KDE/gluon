#include "custominputprivate.h"

using namespace GluonInput;

CustomInputPrivate::CustomInputPrivate()
{
}
CustomInputPrivate::CustomInputPrivate(CustomInputPrivate &other) 
	: QSharedData(other), 
	m_buttons(other.m_buttons), 
	m_absAxis(other.m_absAxis), 
	m_relAxis(other.m_relAxis)
{
}

CustomInputPrivate::~CustomInputPrivate()
{
}