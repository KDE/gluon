#include "inputbuffer.h"

#include"inputbufferprivate.h"

#include <QtCore/QQueue>
#include <QtCore/QHash>
#include <QtCore/QDebug>

using namespace GluonInput;

InputBuffer::InputBuffer()
{
	d = new InputBufferPrivate();
}

InputBuffer::~InputBuffer()
{
}

bool InputBuffer::buttonState(int button)
{
	if(d->buttonState[button].count() == 0)
		return false;
	
	return d->buttonState[button].dequeue();
}

void InputBuffer::setButtonState(int button, bool pressed)
{
	d->buttonState[button].enqueue(pressed);
}

#include "inputbuffer.moc"
