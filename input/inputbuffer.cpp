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