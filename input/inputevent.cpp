#include "inputevent.h"

namespace GluonInput
{
	InputEvent::InputEvent(int code, int value, QEvent::Type eventType) 
	: QEvent(eventType)
	{
		m_code = code;
		m_value = value;
	}

	int InputEvent::code() const 
	{
		return m_code;
	}

	int InputEvent::value() const
	{
		return m_value;
	}
}