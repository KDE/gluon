#ifndef INPUTDEVICEPRIVATE_H
#define INPUTDEVICEPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QMap>
#include <QtCore/QList>

#include "inputthread.h"

namespace GluonInput
{
    class InputDevicePrivate : public QSharedData
    {
        public:
            InputDevicePrivate();
            InputDevicePrivate(InputDevicePrivate &other);

            int m_lastAbsAxis;
            int m_lastRelAxis;

            QList<int> m_buttons;  //list of button pressed
            QList<int> m_forceFeedBack;
            QMap<int, int> m_relAxis; // list of relatif axis Value .  m_relAxis[REL_X] = -1;
            QMap<int, int> m_absAxis; // list of absolue axis value. m_absAxis[ABS_Rx] = 156

            bool m_absMove;
            bool m_relMove;

            InputThread * inputThread;
    };
}

#endif