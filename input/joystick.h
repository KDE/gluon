#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "inputdevice.h"

#include <QtCore/QSharedData>

namespace GluonInput
{
    class InputThread;
    class JoystickPrivate;

    class GLUON_INPUT_EXPORT Joystick : public InputDevice
    {
            Q_OBJECT
        public:
            Joystick(InputThread * inputThread, QObject * parent = 0);

            int axisX() const;
            int axisY()const;
            int axisZ() const;
		
		private slots:
			void joystickMoved(int axis, int distance);

        private:
            QSharedDataPointer<JoystickPrivate> d;
    };
}
//@}
#endif // KCLJOYSTICK_H
