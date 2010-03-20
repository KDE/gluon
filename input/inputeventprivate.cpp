#include "inputeventprivate.h"

using namespace GluonInput;

InputEventPrivate::InputEventPrivate()
{
}

InputEventPrivate::InputEventPrivate(InputEventPrivate &other)
        : QSharedData(other),
        m_code(other.m_code),
        m_value(other.m_value)
{
}