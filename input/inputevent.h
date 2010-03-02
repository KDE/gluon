#ifndef INPUTEVENT_H
#define INPUTEVENT_H

#include "gluon_input_export.h"

#include <QtCore/QEvent>

namespace GluonInput
{
	class GLUON_INPUT_EXPORT InputEvent : public QEvent
	{
	public:
		InputEvent(int code, int value, QEvent::Type eventType);

		int code() const;
		int value() const;
		
	private:
		int m_code;
		int m_value;
	};
}
#endif
