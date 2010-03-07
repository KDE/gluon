#ifndef INPUTEVENT_H
#define INPUTEVENT_H

#include "gluon_input_export.h"
#include "inputeventprivate.h"

#include <QtCore/QEvent>
#include <QtCore/QSharedData>

namespace GluonInput
{
	class GLUON_INPUT_EXPORT InputEvent : public QEvent
	{
	public:
		InputEvent(int code, int value, QEvent::Type eventType);

		int code() const;
		int value() const;
		
	private:
		QSharedDataPointer<InputEventPrivate> d;
	};
}
#endif
