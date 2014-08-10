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

#include "inputdevice.h"
#include "inputparameter.h"

using namespace GluonInput;

class InputDevice::Private
{
    public:
        QString name;
        QList< InputParameter* > parameters;
};

InputDevice::InputDevice( QObject* parent )
    : QObject( parent )
{

}

InputDevice::~InputDevice()
{
}

QString InputDevice::name() const
{
    return d->name;
}

QList< InputParameter* > InputDevice::parameters() const
{
    return d->parameters;
}

InputParameter* InputDevice::parameter(const QString& name) const
{
    for( auto p : d->parameters )
    {
        if( p->name() == name )
            return p;
    }

    return nullptr;
}

InputParameter* InputDevice::parameter(int id) const
{
    return nullptr;
}

void InputDevice::setName(const QString& name)
{
    d->name = name;
}

void InputDevice::setParameters(QList< InputParameter* > parameters)
{
    d->parameters = parameters;
}
