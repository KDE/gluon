#ifndef INPUTEVENT_H
#define INPUTEVENT_H

#include "gluoninput.h"

#include <QtCore/QEvent>

namespace GluonInput
{
	class GLUONINPUTSHARED_EXPORT InputEvent : public QEvent
	{
	public:
		//InputEvent(int code, int value, int usagePage, int usage, int id, QEvent::Type eventType);
		InputEvent(int code, int value, QEvent::Type eventType);
		
		int code() const;
		int value() const;
		//int usagePage() const;
		//int usage() const;
		//int id() const;
		//QEvent::Type eventType();

	private:
		//int m_usagePage;
		//int m_usage;
		int m_code;
		//int m_id;
		int m_value;
	};
}
#endif
