#ifndef DETECT_H
#define DETECT_H

#include <QtCore/QObject>
#include <QtCore/QSharedData>

#include "gluon_input_export.h"

namespace GluonInput
{
	class Joystick;
	class Mouse;
	class Tablet;
	class Keyboard;
    class InputDevice;

    class GLUON_INPUT_EXPORT Detect : public QObject
    {
            Q_OBJECT

        public:
            Detect(QObject * parent = 0);

            virtual void searchDevice() = 0;
            virtual void setAllEnabled() = 0;
            virtual void setAllDisabled() = 0;

            virtual QList<InputDevice *> getInputList() = 0;
            virtual QList<Keyboard *> getKeyboardList() = 0;
            virtual QList<Mouse *> getMouseList() = 0;
            virtual QList<Joystick *> getJoystickList() = 0;
            virtual QList<Tablet *> getTabletList() = 0;
            virtual QList<InputDevice *> getUnknownDeviceList() = 0;

            virtual void addInput(InputDevice *i) = 0;
            virtual void addKeyboard(InputDevice *i) = 0;
            virtual void addMouse(InputDevice *i) = 0;
            virtual void addJoystick(InputDevice *i) = 0;
            virtual void addTablet(InputDevice *i) = 0;
            virtual void addUnknown(InputDevice *i) = 0;
            virtual void clear() = 0;
}
#endif