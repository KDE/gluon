#ifndef KCLINPUTEVENT_H
#define KCLINPUTEVENT_H

#include <QtCore/QEvent>

#include "kcl_export.h"

class KCL_EXPORT KCLInputEvent : public QEvent
{
public:
    KCLInputEvent(int code, int value, int usagePage, int usage, int id, QEvent::Type eventType);

    int code() const;
    int value() const;
    int usagePage() const;
    int usage() const;
    int id() const;
    QEvent::Type eventType();

private:
    int m_usagePage;
    int m_usage;
    int m_code;
    int m_id;
    int m_value;
};

#endif
