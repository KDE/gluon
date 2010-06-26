/******************************************************************************
 * This file is part of the Gluon Development Platform
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
#ifndef CUSTOMINPUT_H
#define CUSTOMINPUT_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtCore/QSharedData>

#include "gluon_input_export.h"
#include "gluondevices.h"

namespace GluonInput
{
    class InputDevice;
    class InputEvent;
    class GluonButtonMapperPrivate;

    class GLUON_INPUT_EXPORT GluonButtonMapper : public QObject
    {
            Q_OBJECT
        public:
            GluonButtonMapper(QObject * parent = 0);
            ~GluonButtonMapper();

            void setButton(const QString &name, InputDevice* input, int keyCode);
            void setButton(const QString &name);
            void remButton(const QString &name);
            void setAbsAxis(const QString &name, InputDevice * input, int axis);
            void setRelAxis(const QString &name, InputDevice* input, int axis);
            void remAbsAxis(const QString &name);
            void remRelAxis(const QString &name);

            QStringList buttonNameList();
            QStringList absAxisNameList();
            QStringList relAxisNameList();

        private:
            QSharedDataPointer<GluonButtonMapperPrivate> d;
    };
}

#endif // KCLCUSTOMINPUT_H
