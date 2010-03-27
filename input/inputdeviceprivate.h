#ifndef INPUTDEVICEPRIVATE_H
#define INPUTDEVICEPRIVATE_H

#include <QtCore/QSharedData>
#include <QtCore/QMap>
#include <QtCore/QList>

//#include "inputthread.h"

namespace GluonInput
{	
	class InputBuffer;
	class InputThread;
	
    class InputDevicePrivate : public QSharedData
    {
        public:
            InputDevicePrivate();

            InputThread * inputThread;
			InputBuffer * inputBuffer;
    };
}

#endif