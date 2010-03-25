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
	if(d->buttonState[button].isEmpty())
	      return false;
	
	bool returnBool = false;
	if(d->buttonState[button].count() > 1)
	{
	  returnBool = d->buttonState[button].dequeue();
	  d->buttonState[button].clear();
	}
	else
	{
	  returnBool = d->buttonState[button].head();
	}
	
	return returnBool; 
}

void InputBuffer::setButtonState(int button, bool pressed)
{
	  if(pressed && d->buttonState[button].isEmpty())
	  {
	    d->buttonState[button].enqueue(pressed);
	  }
	  else if(!pressed && d->buttonState[button].count() == 1)
	  {
	    d->buttonState[button].enqueue(pressed);
	  }
}

#include "inputbuffer.moc"
