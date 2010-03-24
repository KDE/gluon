#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include "gluon_input_export.h"
#include "gluonbuttons.h"

#include <QtCore/QObject>
#include <QtCore/QSharedData>

namespace GluonInput
{
	class InputBufferPrivate;
	
	class GLUON_INPUT_EXPORT InputBuffer : public QObject
	{
		Q_OBJECT
		public:
			InputBuffer();
			~InputBuffer();
		
			bool buttonState(int button);
			void setButtonState(int button, bool pressed);
			
		private:
			QSharedDataPointer<InputBufferPrivate> d;
	};
}

#endif 