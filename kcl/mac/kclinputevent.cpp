#include "kclinputevent.h"

KCLInputEvent::KCLInputEvent(QEvent::Type eventType) : QEvent(eventType)
{
}

int KCLInputEvent::code() const 
{
    return m_code;
}

int KCLInputEvent::usagePage() const
{
    return m_usagePage;
}

int KCLInputEvent::usage() const
{
    return m_usage;
}

int KCLInputEvent::id() const
{
    return m_id;
}

int KCLInputEvent::value() const
{
    return m_value;
}