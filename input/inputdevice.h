#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <QtCore/QMap>
#include <QtCore/QPair>
#include <QtCore/QPoint>
#include <QtCore/QThread>
#include <QtCore/QEvent>
#include <QtCore/QSharedData>
#include <QtCore/QObject>

#include "inputthread.h"
#include "gluondevices.h"

namespace GluonInput
{
    class InputDevicePrivate;

    class GLUON_INPUT_EXPORT InputDevice : public QObject
    {
            Q_OBJECT
			Q_ENUMS(GluonInput::KeyboardButton)

        public:
            InputDevice(InputThread * inputThread, QObject * parent = 0);
            InputDevice();
            ~InputDevice();

            int vendor()const;
            int product()const;
            int version()const;
            int bustype()const;

            const QString deviceName() const;
            GluonInput::DeviceFlag deviceType()const;
            bool button(int code)const;
        /*    bool anyAbsMove();
            bool anyRelMove();
		
#warning this mapping not needed maybe?
		/////////
            int lastAbsAxis()const;
            int lastRelAxis()const;
            int relAxisValue(int code)const;
            int absAxisValue(int code)const;
		/////////*/
            QList<int> buttonCapabilities()const;
            QList<int> absAxisCapabilities()const;
            QList<int> relAxisCapabilities()const;
            AbsVal axisInfo(int axisCode)const;
			bool buttonPressed(int code) const;
			QString buttonName(int code) const;
			QString axisName(int code) const;
		
            bool error()const;
			QString msgError()const;

            void setInputThread(InputThread * inputThread);
            InputThread * inputThread() const;
		
			bool isEnabled() const;
            void setEnabled(bool enable);
		
		private slots:
			void buttonStateChanged(int code, int value);
		
		private:
            void init();

            QSharedDataPointer<InputDevicePrivate> d;
    };
}
#endif // KCLINPUT_H
