#ifndef INPUTBUFFERPRIVATE_H
#define INPUTBUFFERPRIVATE_H

#include <QtCore/QSharedData>

namespace GluonInput
{
	class QHash;
	
	class InputBufferPrivate : public QSharedData
	{
	public:
		InputBufferPrivate();
		InputBufferPrivate(InputBufferPrivate &other);
		
		//QHash<>
	};
}

#endif