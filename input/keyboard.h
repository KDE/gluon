#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "inputdevice.h"

#include <QtCore/QSharedData>

namespace GluonInput
{
    class KeyboardPrivate;
	class InputThread;

	class GLUON_INPUT_EXPORT Keyboard : public InputDevice
	{
		Q_OBJECT
        public:
            Keyboard(InputThread * inputThread, QObject * parent = 0);

        private:
            QSharedDataPointer<KeyboardPrivate> d;
    };
}
#endif // KCLKEYBOARD_H
