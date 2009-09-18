#ifndef KCLINPUTEVENT_H
#define KCLINPUTEVENT_H

#include <QEvent>
#include <linux/input.h>

/**
 * \defgroup KCL KCL
 */
//@{

class KCLInputEvent;
class KCLInputEvent : public QEvent
{
public:
    KCLInputEvent(unsigned short type_,unsigned long tvSec_, unsigned long tvUsec_, unsigned short code_, unsigned short value_);
    KCLInputEvent(struct input_event ev);

    unsigned long tvSec() {
        return m_inputEvent.time.tv_sec;
    }

    unsigned long tvUsec() {
        return m_inputEvent.time.tv_usec;
    }

    unsigned short code() {
        return m_inputEvent.code;
    }

    unsigned int value() {
        return m_inputEvent.value;
    }

    struct input_event inputEvent() {
        return m_inputEvent;
    }
private:
    struct input_event m_inputEvent;
};

//@}
#endif // KCLINPUTEVENT_H
