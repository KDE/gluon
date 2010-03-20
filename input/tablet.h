#ifndef TABLET_H
#define TABLET_H

#include "inputdevice.h"

#include <QtCore/QSharedData>

namespace GluonInput
{
    class InputThread;
    class TabletPrivate;

    class GLUON_INPUT_EXPORT Tablet : public InputDevice
    {
            Q_OBJECT
        public:
            Tablet(InputThread * inputThread, QObject * parent = 0);

        private:
            QSharedDataPointer<TabletPrivate> d;
    };
}
#endif // KCLTABLET_H
