/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
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

#ifndef MOUSE_H
#define MOUSE_H

#include "inputdevice.h"

#include <QtCore/QList>
#include <QtCore/QPoint>
#include <QtGui/QWidget>
#include <QtCore/QSharedData>

namespace GluonInput
{
    class InputThread;
    class MousePrivate;

    class GLUON_INPUT_EXPORT Mouse : public InputDevice
    {
            Q_OBJECT

        public:
            explicit Mouse( InputThread* inputThread, QObject* parent = 0 );

            QPoint position();
            void setPosition(const QPoint& p);

            double sensibility() const;
            void setSensibility( double s );

            void setOrigin( const QPoint p );

            int wheelPosition() const;
            void setWheelPosition(int wp);

            int hWheelPosition() const;
            void setHWheelPosition(int hwp);


        private slots:
            void mouseMoved( int axis, int distance );

        private:
            QSharedDataPointer<MousePrivate> d;
    };
}
//@}
#endif // KCLMOUSE_H
