#ifndef INPUTEVENTPRIVATE_H
#define INPUTEVENTPRIVATE_H

#include <QtCore/QSharedData>

namespace GluonInput
{
	class InputEventPrivate : public QSharedData
	{
	public:
		InputEventPrivate();
		InputEventPrivate(InputEventPrivate &other);
		
		int m_code;
		int m_value;
	};
}

#endif