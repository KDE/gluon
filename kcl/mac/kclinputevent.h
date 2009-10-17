#ifndef KCLINPUTEVENT_H
#define KCLINPUTEVENT_H

#include <QEvent>

class KCLInputEvent : public QEvent
{
public:
    KCLInputEvent( QEvent::Type eventType);

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
