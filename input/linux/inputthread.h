/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H

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
            void stop();

            int vendor()const;
            int product()const;
            int version()const;
            int bustype()const;

            QList<int> buttonCapabilities()const;
	    QList<int> axisCapabilities()const;
            AbsVal axisInfo(int axisCode)const;

            const QString deviceName() const;
            GluonInput::DeviceFlag deviceType()const;

            bool isEnabled() const;

            bool error();
            QString msgError();

            QObject * getParent();

	    signals:
		void axisMoved(int axis, int distance);
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
