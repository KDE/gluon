#include "inputevent.h"
#include "inputeventprivate.h"

namespace GluonInput
{
	InputEvent::InputEvent(int code, int value ,QEvent::Type eventType)
	: QEvent(eventType)
	{
		d = new InputEventPrivate();
		d->m_code = code;
		d->m_value = value;
	}

	int InputEvent::code() const
	{
		return d->m_code;
	}

	int InputEvent::value() const
	{
		return d->m_value;
	}
}