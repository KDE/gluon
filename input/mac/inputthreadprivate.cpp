#include "inputthreadprivate.h"

using namespace GluonInput;

InputThreadPrivate::InputThreadPrivate()
{
}

InputThreadPrivate::InputThreadPrivate(InputThreadPrivate &other)
        : QSharedData(other),
        vendor(other.vendor),
        product(other.product),
        version(other.version),
        bustype(other.bustype),
        deviceName(other.deviceName),
        msgError(other.msgError),
        error(other.error),
        deviceType(other.deviceType),
        buttonCapabilities(other.buttonCapabilities),
        relAxisCapabilities(other.relAxisCapabilities),
        absAxisCapabilities(other.absAxisCapabilities),
        absAxisInfos(other.absAxisInfos),
        xAbsUsage(other.xAbsUsage),
        yAbsUsage(other.yAbsUsage),
        zAbsUsage(other.zAbsUsage),
        device(other.device),
		inputBuffer(NULL)
{
}
