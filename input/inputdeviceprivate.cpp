#include "inputdeviceprivate.h"

using namespace GluonInput;

InputDevicePrivate::InputDevicePrivate()
{
}

InputDevicePrivate::InputDevicePrivate(InputDevicePrivate &other)
	: QSharedData(other),
	m_lastAbsAxis(other.m_lastAbsAxis),
	m_lastRelAxis(other.m_lastRelAxis),
	m_buttons(other.m_buttons),
	m_forceFeedBack(other.m_forceFeedBack),
	m_relAxis(other.m_relAxis),
	m_absAxis(other.m_absAxis),
	m_absMove(other.m_absMove),
	m_relMove(other.m_relMove),
	inputThread(NULL)
{
}