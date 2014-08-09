/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2014 Arjen Hiemstra <ahiemstra@heimr.nl>
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
 *
 */

#ifndef GLUONINPUT_INPUTACTION_H
#define GLUONINPUT_INPUTACTION_H

#include <QtCore/QObject>

#include <core/privatepointer.h>

#include "gluoninput_export.h"

namespace GluonInput
{
    class InputDevice;
    class InputParameter;

    class GLUONINPUT_EXPORT InputAction : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(InputDevice* device READ device WRITE setDevice NOTIFY deviceChanged)
        Q_PROPERTY(InputParameter* parameter READ parameter WRITE setParameter NOTIFY parameterChanged)

        public:
            explicit InputAction(QObject* parent);
            virtual ~InputAction();

            InputDevice* device() const;
            InputParameter* parameter() const;

        public Q_SLOTS:
            void setDevice(InputDevice* device);
            void setParameter(InputParameter* parameter);

        Q_SIGNALS:
            void deviceChanged();
            void parameterChanged();
            
            void triggered();

        private:
            GLUON_PRIVATE_POINTER;
    };
}

#endif // GLUONINPUT_INPUTACTION_H
