#ifndef INPUTBUFFERPRIVATE_H
#define INPUTBUFFERPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QHash>
#include <QtCore/QQueue>

//#include "keydefinitions.h"

namespace GluonInput
{	
	class InputDevice;
	
	class InputBufferPrivate : public QSharedData
	{
	public:
		InputBufferPrivate();
		
		QHash<int, QQueue<bool> > keyState;
	};
}

#endif