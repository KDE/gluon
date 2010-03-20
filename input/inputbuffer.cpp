#include "inputbuffer.h"

#include"inputbufferprivate.h"

using namespace GluonInput;

template<> GLUON_INPUT_EXPORT InputBuffer *GluonCore::Singleton<InputBuffer>::m_instance = 0;

InputBuffer::InputBuffer()
{
	d = new InputBufferPrivate();
}

InputBuffer::~InputBuffer()
{
}

bool InputBuffer::KeyboardKeyPressed(GluonInput::KeyboardKey key)
{
}

bool InputBuffer::MouseButtonPressed(GluonInput::MouseButton button)
{
}

bool InputBuffer::JoystickButtonPressed(GluonInput::JoystickButton button)
{
}

void InputBuffer::SetKeyboardKeyState(GluonInput::KeyboardKey key, bool pressed)
{
}

void InputBuffer::SetMouseButtonState(GluonInput::MouseButton button, bool pressed)
{
}

void InputBuffer::SetJoystickButtonState(GluonInput::JoystickButton button, bool pressed)
{
}