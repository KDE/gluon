#include "inputthreadprivate.h"

using namespace GluonInput;

InputThreadPrivate::InputThreadPrivate()
{
}

InputThreadPrivate::InputThreadPrivate(InputThreadPrivate &other)
	:QSharedData(other),
	m_vendor(other.m_vendor),
	m_product(other.m_product),
	m_version(other.m_version),
	m_bustype(other.m_bustype),
	m_deviceName(other.m_deviceName),
	m_msgError(other.m_msgError),
	m_error(other.m_error),
	m_deviceType(other.m_deviceType),
	m_buttonCapabilities(other.m_buttonCapabilities),
	m_relAxisCapabilities(other.m_relAxisCapabilities),
	m_absAxisCapabilities(other.m_absAxisCapabilities),
	m_absAxisInfos(other.m_absAxisInfos),
	m_xAbsUsage(other.m_xAbsUsage),
	m_yAbsUsage(other.m_yAbsUsage),
	m_zAbsUsage(other.m_zAbsUsage),
	m_device(other.m_device)
{
}
