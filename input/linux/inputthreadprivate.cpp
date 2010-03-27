#include "inputthreadprivate.h"

using namespace GluonInput;

InputThreadPrivate::InputThreadPrivate()
{
}

InputThreadPrivate::InputThreadPrivate(InputThreadPrivate &other)
        : QSharedData(other),
        m_fd(other.m_fd),
        m_device_info(other.m_device_info),
        m_currentEvent(other.m_currentEvent),
        m_devicePath(other.m_devicePath),
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
        m_absAxisInfos(other.m_absAxisInfos)
{
}
