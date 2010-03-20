#ifndef _INPUTTHREAD_H_
#define _INPUTTHREAD_H_

#include "gluon_input_export.h"
#include "keydefinitions.h"
#include "absval.h"

#include <QtCore/QThread>
#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QSharedData>

#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/hid/IOHIDLib.h>

namespace GluonInput
{

    class InputThreadPrivate;

    class GLUON_INPUT_EXPORT InputThread : public QThread
    {
            Q_OBJECT
        public:
            InputThread(IOHIDDeviceRef pDevice, QObject* parent = 0);
            ~InputThread();

            static void deviceReport(void * inContext, IOReturn inResult, void * inSender, IOHIDValueRef inIOHIDValueRef);

            void setEnabled();
            void setDisabled();

            int getJoystickXAxis();
            int getJoystickYAxis();
            int getJoystickZAxis();

            void run();
            void stop();

            int vendor()const;
            int product()const;
            int version()const;
            int bustype()const;

            QList<int> buttonCapabilities()const;
            QList<int> absAxisCapabilities()const;
            QList<int> relAxisCapabilities()const;
            AbsVal axisInfo(int axisCode)const;

            const QString deviceName() const;
            GluonInput::DeviceFlag deviceType()const;

            bool isEnabled() const;

            bool error();
            QString msgError();

            QObject * getParent();

        private:
            void readInformation();

            QSharedDataPointer<InputThreadPrivate> d;
    };
}
#endif