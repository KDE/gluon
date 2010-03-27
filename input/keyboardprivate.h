#ifndef KEYBOARDPRIVATE_H
#define KEYBOARDPRIVATE_H

#include <QtCore/QSharedData>

namespace GluonInput
{
	class KeyboardPrivate : public QSharedData
	{
		public:
			KeyboardPrivate();
			KeyboardPrivate(KeyboardPrivate &other);
	};
}

#endif
