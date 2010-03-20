#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include "core/singleton.h"
#include "gluon_input_export.h"
#include "inputdefinitions.h"

#include <QtCore/QObject>
#include <QtCore/QSharedData>

namespace GluonInput
{
	class InputBufferPrivate;
	
	class GLUON_INPUT_EXPORT InputBuffer : public GluonCore::Singleton<InputBuffer>
	{
	public:
		InputBuffer();
		
		bool KeyboardKeyPressed(GluonInput::KeyboardKey key);
		bool MouseButtonPressed(GluonInput::MouseButton button);
		bool JoystickButtonPressed(GluonInput::JoystickButton button);
		
		void SetKeyboardKeyState(GluonInput::KeyboardKey key, bool pressed);
		void SetMouseButtonState(GluonInput::MouseButton button, bool pressed);
		void SetJoystickButtonState(GluonInput::JoystickButton button, bool pressed);
		
	private:
		~InputBuffer();
		
		QSharedDataPointer<InputBufferPrivate> d;
	};
}

#endif 