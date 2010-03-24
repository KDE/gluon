#ifndef INPUTTHREADPRIVATE_H
#define INPUTTHREADPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QString>

#include "gluonbuttons.h"
#include "absval.h"

#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/hid/IOHIDLib.h>

namespace GluonInput
{
    class InputThreadPrivate : public QSharedData
    {
		
        public:
            InputThreadPrivate();
            InputThreadPrivate(InputThreadPrivate &other);

            int vendor;
            int product;
            int version;
            int bustype;

            QString deviceName;
            QString msgError;

            bool error;

            GluonInput::DeviceFlag deviceType;

            QList<int> buttonCapabilities; // list of button capability. BTN_ESC, BTN_F1 etc....
            QList<int> relAxisCapabilities; // list of rel Axis capability..
            QList<int> absAxisCapabilities; // list of abs Axis capabilty
            QMap<int, AbsVal> absAxisInfos; // each Absolute Axis has a sub info called AbsVal. [ABS_RX] = AbsVal.

            int xAbsUsage;
            int yAbsUsage;
            int zAbsUsage;

            IOHIDDeviceRef device;
    };
}

#endif