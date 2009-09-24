#include "kclinputevent.h"

KCLInputEvent::KCLInputEvent( int type_,unsigned long tvSec_, unsigned long tvUsec_, unsigned short code_, unsigned short value_)
    :QEvent(QEvent::Type(QEvent::User+type_))
{
    struct timeval time;
    time.tv_sec = tvSec_;
    time.tv_usec = tvUsec_;

    m_inputEvent.time = time;
    m_inputEvent.type = type_;
    m_inputEvent.code = code_;
    m_inputEvent.value = value_;
}

KCLInputEvent::KCLInputEvent(struct input_event ev)
    :QEvent(QEvent::Type(QEvent::User+ev.type))
{
    m_inputEvent = ev;
}
