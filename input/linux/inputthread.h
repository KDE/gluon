#ifndef _INPUTTHREAD_H_
#define _INPUTTHREAD_H_

#include <QtCore/QThread>
#include <QtCore/QMap>
#include <QtCore/QSharedData>

#include "gluonbuttons.h"
#include "gluon_input_export.h"
#include "absval.h"
/**
 * \defgroup KCL KCL
 */
//@{

namespace GluonInput
{
    class InputThreadPrivate;

    class GLUON_INPUT_EXPORT InputThread : public QThread
    {
            Q_OBJECT

        public:
            explicit InputThread(const QString& devicePath, QObject *parent = 0);
            ~InputThread();
            void run();

            const QString devicePath() const;

            int getJoystickXAxis();
            int getJoystickYAxis();
            int getJoystickZAxis();
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

	    signals:
			void relAxisMoved(int axis, int distance);
			void absAxisMoved(int axis, int distance);
			void buttonStateChanged(int button, int value);

        private:

            bool openDevice(const QString &devicePath);
            void closeDevice();

            void readInformation();

            QSharedDataPointer<InputThreadPrivate> d;
    };
}
//@}
#endif // KCLTHREAD_H
