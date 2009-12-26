#include "kclinputevent.h"

KCLInputEvent::KCLInputEvent(int code, int value, int usagePage, int usage, int id, QEvent::Type eventType) 
: QEvent(eventType)
{
    m_code = code;
    m_value = value;
    m_usage = usage;
    m_usagePage = usagePage;
    m_id = id;
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