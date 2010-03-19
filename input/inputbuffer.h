#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include "core/singleton.h"
#include "gluon_input_export.h"

#include <QtCore/QObject>
#include <QtCore/QSharedData>

namespace GluonInput
{
	class InputBufferPrivate;
	
	class GLUON_INPUT_EXPORT InputBuffer : public GluonCore::Singleton<InputBuffer>
	{
	public:
		InputBuffer();
		
	private:
		~InputBuffer();
		
		QSharedDataPointer<InputBufferPrivate> d;
	};
}

#endif 