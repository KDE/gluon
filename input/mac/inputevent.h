#ifndef INPUTEVENT_H
#define INPUTEVENT_H

#include <QtCore/QEvent>
#include <QtCore/QSharedData>

namespace GluonInput
{
    class InputEventPrivate;

    class InputEvent : public QEvent
    {
        public:
		
			enum InputTypeFlag 
			{
				Button = QEvent::Type(QEvent::User+1),
				RelativeAxis = QEvent::Type(QEvent::User+2),
				AbsoluteAxis = QEvent::Type(QEvent::User+3)
			};
		
            InputEvent(int code, int value, QEvent::Type eventType);

            int code() const;
            int value() const;

        private:
            QSharedDataPointer<InputEventPrivate> d;
    };
}
#endif
