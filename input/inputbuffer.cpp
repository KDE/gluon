#include "inputbuffer.h"

#include"inputbufferprivate.h"

#include <QtCore/QQueue>
#include <QtCore/QHash>

using namespace GluonInput;

InputBuffer::InputBuffer()
{
	d = new InputBufferPrivate();
}

InputBuffer::~InputBuffer()
{
}

bool InputBuffer::keyState(int key)
{
	return d->keyState[key].dequeue();
}

void InputBuffer::setKeyState(int key, bool pressed)
{
	d->keyState[key].enqueue(pressed);
}

#include "inputbuffer.moc"
