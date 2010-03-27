#ifndef INPUTTHREADPRIVATE_H
#define INPUTTHREADPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>

#include "gluonbuttons.h"
#include "absval.h"

namespace GluonInput
{
    class InputThreadPrivate : public QSharedData
    {
        public:
            InputThreadPrivate();
            InputThreadPrivate(InputThreadPrivate &other);

            int m_fd;
            struct input_id m_device_info;
            struct input_event m_currentEvent;
            QString m_devicePath;

            int m_vendor;
            int m_product;
            int m_version;
            int m_bustype;

            QString m_deviceName;
            QString m_msgError;

            bool m_error;

            GluonInput::DeviceFlag m_deviceType;

            QList<int> m_buttonCapabilities; // list of button capability. BTN_ESC, BTN_F1 etc....
            QList<int> m_relAxisCapabilities; // list of rel Axis capability..
            QList<int> m_absAxisCapabilities; // list of abs Axis capabilty
            QMap<int, AbsVal> m_absAxisInfos; // each Absolute Axis has a sub info called AbsVal. [ABS_RX] = AbsVal.
    };
}
#endif
