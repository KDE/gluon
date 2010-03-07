#include "inputdetectionprivate.h"

using namespace GluonInput;

InputDetectionPrivate::InputDetectionPrivate()
{
}

InputDetectionPrivate::InputDetectionPrivate(InputDetectionPrivate &other)
	: QSharedData(other),
	m_instance(other.m_instance)
{
}