#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "inputdevice.h"

namespace GluonInput
{
	class InputThread;

	class GLUON_INPUT_EXPORT KeyBoard : public InputDevice
	{
        Q_OBJECT
        public:
            KeyBoard(InputThread * inputThread, QObject * parent = 0);
	};
}
#endif // KCLKEYBOARD_H
