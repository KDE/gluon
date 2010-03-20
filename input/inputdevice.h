#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <QtCore/QMap>
#include <QtCore/QPair>
#include <QtCore/QPoint>
#include <QtCore/QThread>
#include <QtCore/QEvent>
#include <QtCore/QSharedData>

#include "code.h"
#include "inputthread.h"
#include "inputevent.h"

namespace GluonInput
{
    class InputDevicePrivate;

    class GLUON_INPUT_EXPORT InputDevice : public QObject
    {
            Q_OBJECT

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
            int anyPress() const;
            bool anyAbsMove();
            bool anyRelMove();
            int lastAbsAxis()const;
            int lastRelAxis()const;
            int relAxisValue(int code)const;
            int absAxisValue(int code)const;
            QList<int> buttonCapabilities()const;
            QList<int> absAxisCapabilities()const;
            QList<int> relAxisCapabilities()const;
            AbsVal axisInfo(int axisCode)const;
            bool error()const;
            QString msgError()const;
            bool isEnabled() const;

            void setInputThread(InputThread * inputThread);
            InputThread * inputThread() const;

        signals:
            void eventSent(GluonInput::InputEvent * event);
            void buttonPressed(int code);
            void buttonReleased(int code);
            void absAxisChanged(int axe, int code);
            void relAxisChanged(int axe, int code);
            void pressed();
            void moved();

        public slots:
            void setEnabled();
            void setDisabled();

        private:
            bool event(QEvent * evt);
            void init();

            QSharedDataPointer<InputDevicePrivate> d;
    };
}
#endif // KCLINPUT_H
