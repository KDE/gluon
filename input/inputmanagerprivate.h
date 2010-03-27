#ifndef INPUTMANAGERPRIVATE_H
#define INPUTMANAGERPRIVATE_H

#include <QtCore/QSharedData>

namespace GluonInput
{
	class Detect;
	class InputManagerPrivate : public QSharedData
	{
	public:
		InputManagerPrivate();
		InputManagerPrivate(InputManagerPrivate &other);

		Detect * m_instance;
	};
}
#endif
