#include "inputevent.h"

namespace GluonInput
{
	/*InputEvent::InputEvent(int code, int value, int usagePage, int usage, int id, QEvent::Type eventType) 
	: QEvent(eventType)
	{
		m_code = code;
		m_value = value;
		m_usage = usage;
		m_usagePage = usagePage;
		m_id = id;
	}*/
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

	/*int InputEvent::usagePage() const
	{
		return m_usagePage;
	}

	int InputEvent::usage() const
	{
		return m_usage;
	}

	int InputEvent::id() const
	{
		return m_id;
	}*/

	int InputEvent::value() const
	{
		return m_value;
	}
}