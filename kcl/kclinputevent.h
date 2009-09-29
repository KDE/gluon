#ifndef KCLINPUTEVENT_H
#define KCLINPUTEVENT_H

#include <QEvent>
#include <linux/input.h>
#include "kcl_export.h"
/**
 * \defgroup KCL KCL
 */
//@{

class KCLInputEvent;
class KCL_EXPORT KCLInputEvent : public QEvent
{
public:
    KCLInputEvent(int type_,unsigned long tvSec_, unsigned long tvUsec_, unsigned short code_, unsigned short value_);
    KCLInputEvent(struct input_event ev);

    unsigned long tvSec() const {
        return m_inputEvent.time.tv_sec;
    }

    unsigned long tvUsec() const {
        return m_inputEvent.time.tv_usec;
    }

    unsigned short code() const {
        return m_inputEvent.code;
    }

    unsigned int value() const {
        return m_inputEvent.value;
    }

    struct input_event inputEvent() const {
        return m_inputEvent;
    }
private:
    struct input_event m_inputEvent;
};

//@}
#endif // KCLINPUTEVENT_H
