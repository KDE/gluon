#ifndef INPUTBUFFERPRIVATE_H
#define INPUTBUFFERPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QHash>
#include <QtCore/QQueue>

//#include "keydefinitions.h"

namespace GluonInput
{
	class InputBufferPrivate : public QSharedData
	{
	public:
		InputBufferPrivate();

		QHash<int, QQueue<bool> > buttonState;
	};
}

#endif
